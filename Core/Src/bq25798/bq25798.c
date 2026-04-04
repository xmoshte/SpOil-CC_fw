/*
 * bq25790.c
 *
 *  Created on: Oct 4, 2025
 *  Author: moshte
 */
#include "bq25798.h"
#include "bq25798_int.h"

enum registers{
	REG00_Minimal_System_Voltage = 0x00,
	REG01_Charge_Voltage_Limit = 0x01,
	REG03_Charge_Current_Limit = 0x03,
	REG05_Input_Voltage_Limit = 0x05,
	REG06_Input_Current_Limit = 0x06,
	REG08_Precharge_Control = 0x08,
	REG09_Termination_Control = 0x09,
	REG0A_Recharge_Control = 0x0A,
	REG0B_VOTG_regulation = 0x0B,
	REG0D_IOTG_regulation = 0x0D,
	REG0E_Timer_Control = 0x0E,
	REG0F_Charger_Control_0 = 0x0F,
	REG10_Charger_Control_1 = 0x10,
	REG11_Charger_Control_2 = 0x11,
	REG12_Charger_Control_3 = 0x12,
	REG13_Charger_Control_4 = 0x13,
	REG14_Charger_Control_5 = 0x14,
	REG15_Reserved = 0x15,
	REG16_Temperature_Control = 0x16,
	REG17_NTC_Control_0 = 0x17,
	REG18_NTC_Control_1 = 0x18,
	REG19_ICO_Current_Limit = 0x19,
	REG1B_Charger_Status_0 = 0x1B,
	REG1C_Charger_Status_1 = 0x1C,
	REG1D_Charger_Status_2 = 0x1D,
	REG1E_Charger_Status_3 = 0x1E,
	REG1F_Charger_Status_4 = 0x1F,
	REG20_FAULT_Status_0 = 0x20,
	REG21_FAULT_Status_1 = 0x21,
	REG22_Charger_Flag_0 = 0x22,
	REG23_Charger_Flag_1 = 0x23,
	REG24_Charger_Flag_2 = 0x24,
	REG25_Charger_Flag_3 = 0x25,
	REG26_FAULT_Flag_0 = 0x26,
	REG27_FAULT_Flag_1 = 0x27,
	REG28_Charger_Mask_0 = 0x28,
	REG29_Charger_Mask_1 = 0x29,
	REG2A_Charger_Mask_2 = 0x2A,
	REG2B_Charger_Mask_3 = 0x2B,
	REG2C_FAULT_Mask_0 = 0x2C,
	REG2D_FAULT_Mask_1 = 0x2D,
	REG2E_ADC_Control = 0x2E,
	REG2F_ADC_Function_Disable_0 = 0x2F,
	REG30_ADC_Function_Disable_1 = 0x30,
	REG31_IBUS_ADC = 0x31,
	REG33_IBAT_ADC = 0x33,
	REG35_VBUS_ADC = 0x35,
	REG37_VAC1_ADC = 0x37,
	REG39_VAC2_ADC = 0x39,
	REG3B_VBAT_ADC = 0x3B,
	REG3D_VSYS_ADC = 0x3D,
	REG3F_TS_ADC = 0x3F,
	REG41_TDIE_ADC = 0x41,
	REG43_Dplus_ADC = 0x43,
	REG45_Dminus_ADC = 0x45,
	REG47_DPDM_Driver = 0x47,
	REG48_Part_Information = 0x48
};

/*Change according to the masks you are targeting. To be passed to the setInterrupts function*/
//static qbyte targIntrMsk = (IINDPM_MASK | CHG_MASK | VSYS_MASK);

int bqWriteReg(bq_ref dev, byte reg, byte *data, size_t len){

	return dev->bqbus.write(dev->bqbus.ctx, reg, data, len);
};

int bqReadReg(bq_ref dev, byte reg, byte *data, size_t len){

	return dev->bqbus.read(dev->bqbus.ctx, reg, data, len);
};

void bq_delay(bq_ref dev, qbyte usec){
    dev->bqbus.delay_us(dev->bqbus.ctx, usec);
}

/**
 * @brief: This function atomically modifies specific bits in a register without affecting the other bits
 * @param: reg - The 8-bit register address to modify
 * @param: bit - The starting bit position (0-7) where the mask and value should be applied (shifts the mask and value left by this many bits)
 * @param: mask -  An 8-bit mask defining which bits to modify (1s indicate bits to change; typically a contiguous block like 0x03 for the lowest 2 bits)
 * @param: val -  The new value to set in the masked bit positions (should be pre-shifted or sized to fit the mask, e.g., 0-3 for a 2-bit mask)
 */

void bqSetReg(bq_ref dev, byte reg, byte bit, byte mask, byte val)
{
	byte tmp;

	bqReadReg(dev, reg, &tmp, sizeof(tmp));

	tmp = tmp & (byte)~(mask << bit);
	tmp = tmp | (byte)(val << bit);

	bqWriteReg(dev, reg, &tmp, sizeof(tmp));
}

bq_ref bq_init(const struct bq_bus_delegate *delegate)
{
    if (!delegate || !delegate->read || !delegate->write || !delegate->delay_us) {
        errno = EINVAL;
        return NULL;
    }

    struct bq25798 *dev = calloc(1, sizeof(*dev));
    if (!dev) {
        return NULL;
    }

    dev->bqbus = *delegate;

    logString("BQ25798: I2C2 bus initialised\r\n");

    return dev;
}

void bqReadPartInfo(bq_ref dev, struct bq25790PartInfo *p){
	byte val;

    bqReadReg(dev, REG48_Part_Information, &val, sizeof(val));

	memset(p, 0, sizeof(*p));

	p->dvc_rvsn = val & 7U;
	p->dvc_pn = (val >> 3) & 7U;
}

void bqReset(bq_ref dev){
    bqSetReg(dev, REG09_Termination_Control, 6, 0x01, 1);
}

void bqEnOrMaskInterrupt(bq_ref dev, qbyte targIntMsk, qbyte bqIntMsk, byte intrMskReg, byte startBit, byte enOrDis){
	if(targIntMsk & bqIntMsk){
		bqSetReg(dev, intrMskReg, startBit, 1, !enOrDis);
	}
}

void bqReadStatus1_3(bq_ref dev, struct bq25790Status1_3 *p){
	byte val0; byte val1; byte val2; byte val3;

	assert(p != NULL);

    bqReadReg(dev, REG1B_Charger_Status_0, &val0, sizeof(val0));
    bqReadReg(dev, REG1C_Charger_Status_1, &val1, sizeof(val1));
    bqReadReg(dev, REG1D_Charger_Status_2, &val2, sizeof(val2));
    bqReadReg(dev, REG1E_Charger_Status_3, &val3, sizeof(val3));

	memset(p, 0, sizeof(*p));

	p->vbus_present_stat = val0 & 1U;
	p->ac1_present_stat = (val0 >> 1) & 1U;
	p->ac2_present_stat = (val0 >> 2) & 1U;
	p->pg_stat = (val0 >> 3) & 1U;
//	p->poorsrc_stat = (val0 >> 4) & 1U;
	p->wd_stat = (val0 >> 5) & 1U;
	p->vindpm_stat = (val0 >> 6) & 1U;
	p->iindpm_stat = (val0 >> 7) & 1U;

	p->bc1_2_done_stat = val1 & 1U;
	p->vbus_stat = (val1 >> 1) & 15U;
	p->chg_stat_2 = (val1 >> 5) & 7U;

	p->vbat_present_stat = val2 & 1U;
	p->dpdm_stat = (val2 >> 1) & 1U;
	p->treg_stat = (val2 >> 2) & 1U;
	p->ico_stat = (val2 >> 6) & 3U;

	p->prechg_tmr_stat = (val3 >> 1) & 1U;
	p->trichg_tmr_stat = (val3 >> 2) & 1U;
	p->chg_tmr_stat = (val3 >> 3) & 1U;
	p->vsys_stat = (val3 >> 4) & 1U;
	p->adc_done_stat = (val3 >> 5) & 1U;
	p->acrb1_stat = (val3 >> 6) & 1U;
	p->acrb2_stat = (val3 >> 7) & 1U;
}

void bqLogChargerStatusFault(bq_ref dev, struct bq25790Status1_3 *f){
    if (!f) return;

    logString("\r\n--- BQ25798 Charger Status ---\r\n");

    if (f->vbus_present_stat)   logString("VBUS present\r\n");
    if (f->ac1_present_stat)    logString("VAC1 present\r\n");
    if (f->ac2_present_stat)    logString("VAC2 present\r\n");
    if (f->pg_stat)             logString("Power good\r\n");
    if (f->wd_stat)             logString("WD timer expired\r\n");
    if (f->vindpm_stat)         logString("In VINDPM regulation or VOTG regulation\r\n");
    if (f->iindpm_stat)         logString("In IINDPM regulation or IOTG regulation\r\n");

    if (f->vbat_present_stat)   logString("VBAT present\r\n");
    if (f->dpdm_stat)           logString("The D+/D- detection is ongoing\r\n");
    if (f->treg_stat)           logString("Device in thermal regulation\r\n");
    if (!f->ico_stat)           logString("ICO disabled\r\n");

    logString("-----------------------------\r\n");
}

void bqReadTempStatus(bq_ref dev, struct bq25790Status4 *q){
	byte val4;

	assert(q != NULL);

	bqReadReg(dev, REG1F_Charger_Status_4, &val4, sizeof(val4));

	memset(q, 0, sizeof(*q));

	q->ts_hot_stat = val4 & 1U;
	q->ts_warm_stat = (val4 >> 1) & 1U;
	q->ts_cool_stat = (val4 >> 2) & 1U;
	q->ts_cold_stat = (val4 >> 3) & 1U;
	q->vbatotg_low_stat = (val4 >> 4) & 1U;
}

void bqRprtStsTempRng(bq_ref dev, struct bq25790Status4 *p){
	bqReadTempStatus(dev, p);

	if(p->ts_hot_stat){
		logString("TS status in hot range/r/n");
	}

	if(p->ts_warm_stat){
		logString("TS status in warm range/r/n");
	}

	if(p->ts_cool_stat){
        logString("TS status in cool range/r/n");
	}

	if(p->ts_cold_stat){
	    logString("TS status in cold range/r/n");
	}
}

void bqReadStatusFault(bq_ref dev, struct bq25790StatusFault *r){
	byte val5; byte val6;

	assert(r != NULL);

	bqReadReg(dev, REG20_FAULT_Status_0, &val5, sizeof(val5));
	bqReadReg(dev, REG21_FAULT_Status_1, &val6, sizeof(val6));

	memset(r, 0, sizeof(*r));

	r->vac1_ovp_stat = val5 & 1U;
	r->vac2_ovp_stat = (val5 >> 1) & 1U;
	r->ibat_ocp_stat = (val5 >> 3) & 1U;
	r->ibus_ocp_stat = (val5 >> 4) & 1U;
	r->vbat_ovp_stat = (val5 >> 5) & 1U;
	r->vbus_ovp_stat = (val5 >> 6) & 1U;
	r->ibat_reg_stat = (val5 >> 7) & 1U;

	r->thut_stat = (val6 >> 2) & 1U;
	r->otg_uvp_stat = (val6 >> 4) & 1U;
	r->otg_ovp_stat = (val6 >> 5) & 1U;
	r->vsys_ovp_stat = (val6 >> 6) & 1U;
	r->vsys_short_stat = (val6 >> 7) & 1U;
}

void bqLogStatusFault(bq_ref dev, struct bq25790StatusFault *f){
    if (!f) return;

    logString("\r\n--- BQ25798 Fault Status ---\r\n");

    if (f->vac1_ovp_stat)   logString("VAC1 OVP Fault\r\n");
    if (f->vac2_ovp_stat)   logString("VAC2 OVP Fault\r\n");
    if (f->conv_ocp_stat)   logString("Converter OCP Fault\r\n");
    if (f->ibat_ocp_stat)   logString("IBAT OCP Fault\r\n");
    if (f->ibus_ocp_stat)   logString("IBUS OCP Fault\r\n");
    if (f->vbat_ovp_stat)   logString("VBAT OVP Fault\r\n");
    if (f->vbus_ovp_stat)   logString("VBUS OVP Fault\r\n");
    if (f->ibat_reg_stat)   logString("IBAT Regulation Active\r\n");

    if (f->thut_stat)       logString("Thermal Shutdown\r\n");
    if (f->otg_uvp_stat)    logString("OTG UVP Fault\r\n");
    if (f->otg_ovp_stat)    logString("OTG OVP Fault\r\n");
    if (f->vsys_ovp_stat)   logString("VSYS OVP Fault\r\n");
    if (f->vsys_short_stat) logString("VSYS Short Fault\r\n");

    logString("-----------------------------\r\n");
}

void bqRprtPartInfo(bq_ref dev, struct bq25790PartInfo *p){
	bqReadPartInfo(dev, p);

	char buf[16];

	nextLine();
	logString("DEVICE REVISION:");
	sprintf(buf, "%u", p->dvc_rvsn);
    logString(buf);
    logString("\r\n");

    logString("DEVICE PART NUMBER:");
    sprintf(buf, "%u", p->dvc_pn);
    logString(buf);
    logString("\r\n");
}

void bqRprtStsSftyTmrExp(bq_ref dev, struct bq25790Status1_3 *p){
	bqReadStatus1_3(dev, p);
	if(p->prechg_tmr_stat || p->trichg_tmr_stat || p->chg_tmr_stat){
       logString("Charge safety timer expired. Battery likely faulty/r/n");
	}
}


void bqSetWatchdogTimer(bq_ref dev, enum bq25790Watchdog opt){
	bqSetReg(dev, REG10_Charger_Control_1, 0, 0x07, opt);
}

void bqSetTsIgnore(bq_ref dev, byte opt){
	bqSetReg(dev, REG18_NTC_Control_1, 0, 0x01, opt);
}

void bqSetMinimalSystemVoltageLimit(bq_ref dev, qbyte mVolts){
	qbyte regVal = (mVolts/250);

	if(regVal > 64){
	   regVal= 64;
	}

	bqSetReg(dev, REG00_Minimal_System_Voltage, 0, 0x1F, (byte)regVal);
}

void bqSetChargeVoltageLimit(bq_ref dev, qbyte mVolts){
	qbyte regVal = (mVolts/10);

	if(regVal > 1800){
	   regVal= 1800;
	}

	byte lVal = regVal & 0xFF;
	byte hVal = (regVal >> 8) & 7U;

	bqSetReg(dev, REG01_Charge_Voltage_Limit, 0, 0xFF, lVal);
	bqSetReg(dev, REG01_Charge_Voltage_Limit, 8, 0x07, hVal);
}

void bqSetChargeCurrentLimit(bq_ref dev, qbyte amperes){
	qbyte mAmps = amperes * 1000;
	qbyte regVal = (mAmps/10);

	if(regVal > 500){
	   regVal= 500;
	}

	byte lVal = regVal & 0xFF;
	byte hVal = (regVal >> 8) & 1U;

	bqSetReg(dev, REG03_Charge_Current_Limit, 0, 0xFF, lVal);
	bqSetReg(dev, REG03_Charge_Current_Limit, 8, 0x01, hVal);
}

void bqSetInputVoltageLimit(bq_ref dev, qbyte volts){
	qbyte mVolts = volts * 1000;
	qbyte regVal = (mVolts/100);

	if(regVal > 220){
	   regVal= 220;
	}

	bqSetReg(dev, REG05_Input_Voltage_Limit, 0, 0xFF, (byte)regVal);
}

void bqSetInputCurrentLimit(bq_ref dev, qbyte amperes){
	qbyte mAmps = amperes * 1000;
	qbyte regVal = (mAmps/10);

	if(regVal > 330){
	   regVal= 330;
	}

	byte lVal = regVal & 0xFF;
	byte hVal = (regVal >> 8) & 1U;

	bqSetReg(dev, REG06_Input_Current_Limit, 0, 0xFF, lVal);
	bqSetReg(dev, REG06_Input_Current_Limit, 8, 0x01, hVal);
}

void bqSetFastChargeVoltageThreshold(bq_ref dev, enum bq25790FastChargeThreshold opt){
     bqSetReg(dev, REG08_Precharge_Control, 6, 0x03, opt);
}

void bqSetPrechargeCurrentLimit(bq_ref dev, qbyte amperes){
	qbyte mAmps = amperes * 1000;
	qbyte regVal = (mAmps/40);

	if(regVal > 50){
	   regVal= 50;
	}

	bqSetReg(dev, REG08_Precharge_Control, 0, 0x3F, (byte)regVal);
}

void bqSetTerminationCurrent(bq_ref dev, qbyte mAmps){
   qbyte regVal = (mAmps/40);

   if(regVal > 25){
	  regVal = 25;
   }

   bqSetReg(dev, REG09_Termination_Control, 0, 0x1F, (byte)regVal);
}

void bqSetRechargeThreshold(bq_ref dev, byte volts){
	qbyte mVolts = volts * 1000;
	qbyte regVal = (mVolts/50);

	if(regVal > 16){
	   regVal= 16;
	}

	bqSetReg(dev, REG0A_Recharge_Control, 0, 0x0F, (byte)regVal);
}

int16_t bqReadIBus(bq_ref dev){
	int16_t mAmps = 0;
	byte buf[2];
	char bufStrng[16];

	HAL_StatusTypeDef sts = bqReadReg(dev, REG31_IBUS_ADC, buf, sizeof(mAmps));

	if(sts == HAL_OK){
	   mAmps = (int16_t)((buf[1] << 8) | buf[0]);
	   sprintf(bufStrng, "%hd", mAmps);
	   logString("IBUS:");
	   logString(bufStrng);
	   nextLine();
	   return mAmps;
	}
	return mAmps;
}

int16_t bqReadVBus(bq_ref dev){
	int16_t mVolts = 0;
	byte buf[2];
	char bufStrng[16];

	HAL_StatusTypeDef sts = bqReadReg(dev, REG35_VBUS_ADC, buf, sizeof(mVolts));

	if(sts == HAL_OK){
	   mVolts = (int16_t)((buf[1] << 8) | buf[0]);
	   sprintf(bufStrng, "%hd", mVolts);
	   logString("VBUS:");
	   logString(bufStrng);
	   nextLine();
	   return mVolts;
	}
	return mVolts;
}

int16_t bqReadIBat(bq_ref dev){
	int16_t mAmps = 0;
	byte buf[2];
	char bufStrng[16];

	HAL_StatusTypeDef sts = bqReadReg(dev, REG33_IBAT_ADC, buf, sizeof(mAmps));

	if(sts == HAL_OK){
	   mAmps = (int16_t)((buf[1] << 8) | buf[0]);
	   sprintf(bufStrng, "%hd", mAmps);
	   logString("IBAT:");
	   logString(bufStrng);
	   nextLine();
	   return mAmps;
	}
	return mAmps;
}

int16_t bqReadVBat(bq_ref dev){
	int16_t mVolts = 0;
	byte buf[2];
	char bufStrng[16];

	HAL_StatusTypeDef sts = bqReadReg(dev, REG3B_VBAT_ADC, buf, sizeof(mVolts));

	if(sts == HAL_OK){
	   mVolts = (int16_t)((buf[1] << 8) | buf[0]);
	   sprintf(bufStrng, "%hd" , mVolts);
	   logString("VBAT:");
	   logString(bufStrng);
	   nextLine();
	   return mVolts;
	}
	return mVolts;
}

int16_t bqReadVSys(bq_ref dev){
	int16_t mVolts = 0;
	byte buf[2];
	char bufStrng[16];

	HAL_StatusTypeDef sts = bqReadReg(dev, REG3D_VSYS_ADC, buf, sizeof(mVolts));

	if(sts == HAL_OK){
	   mVolts = (int16_t)((buf[1] << 8) | buf[0]);
	   sprintf(bufStrng, "%hd" , mVolts);
	   logString("VSYS:");
	   logString(bufStrng);
	   nextLine();
	   return mVolts;
	}
	return mVolts;
}


