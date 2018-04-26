#include "dictionary.h"

Dictionary::Dictionary()
{
	//�۲�Ҫ��
	//�����ӷ���
	map.insert("aec", "WD_Avg2MWD");
	//�����ӷ���
	map.insert("afc", "WS_Avg2MWS1");
	//ʮ���ӷ���
	map.insert("aed", "WD_Avg10MWD");
	//ʮ���ӷ���+����
	map.insert("afd", "WS_Avg10MWS1");
	//�����ٷ���
	map.insert("aeg", "WD_MaxWSD");
	//������
	map.insert("afda", "WS_MaxWS1");
	//�����ٳ���ʱ��
	map.insert("afdb", "WS_MaxWS1T");
	//��ǰʱ��˲ʱ����
	map.insert("aea", "WD_IWD");
	//��ǰʱ��˲ʱ����
	map.insert("afa", "WS_IWS1");
	//1������˲ʱ�����ٷ���
	map.insert("aef", "WD_Max1MIWSD");
	//1������˲ʱ������
	map.insert("afaa", "WS_Max1MWS1");
	//������ٷ���
	map.insert("aee", "WD_EWSD");
	//�������
	map.insert("afae", "WS_EWS1");
	//������ٳ���ʱ��
	map.insert("afaf", "WS_EWS1T");

	//��һ������
	map.insert("aaa", "AT_AT1");
	//��һ���������ֵ
	map.insert("aaaa", "AT_MaxAT1");
	//��һ���������ֵ����ʱ��
	map.insert("aaab", "AT_MaxAT1T");
	//��һ��������Сֵ
	map.insert("aaac", "AT_MinAT1");
	//��һ��������Сֵ����ʱ��
	map.insert("aaad", "AT_MinAT1T");
	//��һ��ʪ��
	map.insert("ada", "AH_RH1");
	//��һ��ʪ����Сֵ
	map.insert("adac", "AH_MinRH1");
	//��һ��ʪ����Сֵ����ʱ��
	map.insert("adad", "AH_MinRH1T");
	//��һ��ˮ��ѹ
	map.insert("adc", "AH_WVP1");
	//��һ��¶���¶�
	map.insert("adb", "AH_DPT1");

	//�ڶ�������
	map.insert("aaa1", "AT_AT2");
	//�ڶ����������ֵ
	map.insert("aaa1a", "AT_MaxAT2");
	//�ڶ����������ֵ����ʱ��
	map.insert("aaa1b", "AT_MaxAT2T");
	//�ڶ���������Сֵ
	map.insert("aaa1c", "AT_MinAT2");
	//�ڶ���������Сֵ����ʱ��
	map.insert("aaa1d", "AT_MinAT2T");
	//�ڶ���ʪ��
	map.insert("ada1", "AH_RH2");
	//�ڶ���ʪ����Сֵ
	map.insert("ada1c", "AH_MinRH2");
	//�ڶ���ʪ����Сֵ����ʱ��
	map.insert("ada1d", "AH_MinRH2T");
	//�ڶ���ˮ��ѹ
	map.insert("adc1", "AH_WVP2");
	//�ڶ���¶���¶�
	map.insert("adb1", "AH_DPT2");

	//����������
	map.insert("aaa2", "AT_AT3");
	//�������������ֵ
	map.insert("aaa2a", "AT_MaxAT3");
	//�������������ֵ����ʱ��
	map.insert("aaa2b", "AT_MaxAT3T");
	//������������Сֵ
	map.insert("aaa2c", "AT_MinAT3");
	//������������Сֵ����ʱ��
	map.insert("aaa2d", "AT_MinAT3T");
	//������ʪ��
	map.insert("ada2", "AH_RH3");
	//������ʪ����Сֵ
	map.insert("ada2c", "AH_MinRH3");
	//������ʪ����Сֵ����ʱ��
	map.insert("ada2d", "AH_MinRH3T");
	//������ˮ��ѹ
	map.insert("adc2", "AH_WVP3");
	//������¶���¶�
	map.insert("adb2", "AH_DPT3");

	//���Ĳ�����
	map.insert("aaa3", "AT_AT4");
	//���Ĳ��������ֵ
	map.insert("aaa3a", "AT_MaxAT4");


	//���Ĳ��������ֵ����ʱ��
	map.insert("aaa3b", "AT_MaxAT4T");
	//���Ĳ�������Сֵ
	map.insert("aaa3c", "AT_MinAT4");
	//���Ĳ�������Сֵ����ʱ��
	map.insert("aaa3d", "AT_MinAT4T");
	//���Ĳ�ʪ��
	map.insert("ada3", "AH_RH4");
	//���Ĳ�ʪ����Сֵ
	map.insert("ada3c", "AH_MinRH4");
	//���Ĳ�ʪ����Сֵ����ʱ��
	map.insert("ada3d", "AH_MinRH4T");
	//���Ĳ�ˮ��ѹ
	map.insert("adc3", "AH_WVP4");
	//���Ĳ�¶���¶�
	map.insert("adb3", "AH_DPT4");

	//��һ�����
	map.insert("ab5", "ST_ST1");
	//��һ��������ֵ
	map.insert("ab5a", "ST_MaxST1");
	//��һ��������ֵ����ʱ��
	map.insert("ab5b", "ST_MaxST1T");
	//��һ�������Сֵ
	map.insert("ab5c", "ST_MinST1");
	//��һ�������Сֵ����ʱ��
	map.insert("ab5d", "ST_MinST1T");

	//�ڶ������
	map.insert("ab10", "ST_ST2");
	//�ڶ���������ֵ
	map.insert("ab10a", "ST_MaxST2");
	//�ڶ���������ֵ����ʱ��
	map.insert("ab10b", "ST_MaxST2T");
	//�ڶ��������Сֵ
	map.insert("ab10c", "ST_MinST2");
	//�ڶ��������Сֵ����ʱ��
	map.insert("ab10d", "ST_MinST2T");

	//���������
	map.insert("ab15", "ST_ST3");
	//������������ֵ
	map.insert("ab15a", "ST_MaxST3");
	//������������ֵ����ʱ��
	map.insert("ab15b", "ST_MaxST3T");
	//�����������Сֵ
	map.insert("ab15c", "ST_MinST3");
	//�����������Сֵ����ʱ��
	map.insert("ab15d", "ST_MinST3T");

	//���Ĳ����
	map.insert("ab20", "ST_ST4");
	//���Ĳ�������ֵ
	map.insert("ab20a", "ST_MaxST4");
	//���Ĳ�������ֵ����ʱ��
	map.insert("ab20b", "ST_MaxST4T");
	//���Ĳ������Сֵ
	map.insert("ab20c", "ST_MinST4");
	//���Ĳ������Сֵ����ʱ��
	map.insert("ab20d", "ST_MinST4T");

	//��������
	map.insert("ab30", "ST_ST5");
	//�����������ֵ
	map.insert("ab30a", "ST_MaxST5");
	//�����������ֵ����ʱ��
	map.insert("ab30b", "ST_MaxST5T");
	//����������Сֵ
	map.insert("ab30c", "ST_MinST5");
	//����������Сֵ����ʱ��
	map.insert("ab30d", "ST_MinST5T");

	//���������
	map.insert("ab40", "ST_ST6");
	//������������ֵ
	map.insert("ab40a", "ST_MaxST6");
	//������������ֵ����ʱ��
	map.insert("ab40b", "ST_MaxST6T");
	//�����������Сֵ
	map.insert("ab40c", "ST_MinST6");
	//�����������Сֵ����ʱ��
	map.insert("ab40d", "ST_MinST6T");

	//���߲����
	map.insert("ab50", "ST_ST7");
	//���߲�������ֵ
	map.insert("ab50a", "ST_MaxST7");
	//���߲�������ֵ����ʱ��
	map.insert("ab50b", "ST_MaxST7T");
	//���߲������Сֵ
	map.insert("ab50c", "ST_MinST7");
	//���߲������Сֵ����ʱ��
	map.insert("ab50d", "ST_MinST7T");

	//�ڰ˲����
	map.insert("ab50", "ST_ST8");
	//�ڰ˲�������ֵ
	map.insert("ab50a", "ST_MaxST8");
	//�ڰ˲�������ֵ����ʱ��
	map.insert("ab50b", "ST_MaxST8T");
	//�ڰ˲������Сֵ
	map.insert("ab50c", "ST_MinST8");
	//�ڰ˲������Сֵ����ʱ��
	map.insert("ab50d", "ST_MinST8T");

	//����1�������¶ȣ�
	map.insert("aba", "OT_GT");
	//�����¶�
	map.insert("aab", "OT_IT");
	//�ܷ���
	map.insert("aja", "R_TRI");
	//�ܷ����ط���
	map.insert("ajaa", "R_TRD");
	//�ܷ����ն����ֵ
	map.insert("ajae", "R_MaxMTRI");
	//�����Ч
	map.insert("aji", "R_PERI");
	//�����Ч�����ط���
	map.insert("ajia", "R_PERD");
	//CO2Ũ��
	map.insert("asa", "CO2IC");
	//CO2Ũ�����ֵ
	map.insert("asaa", "MaxCO2C");
	//CO2Ũ�����ֵ����ʱ��
	map.insert("asab", "MaxCO2CT");
	//CO2Ũ����Сֵ
	map.insert("asac", "MinCO2Cntr");
	//CO2Ũ����Сֵ����ʱ��
	map.insert("asad", "MinDayCO2CT");
	//����
	map.insert("aia", "Evaporat");
	//������
	map.insert("aje", "R_CR");
	//�������
	map.insert("ajb", "R_RR");
	//�����߷���
	map.insert("ajg", "R_UR");
	//���泤������
	map.insert("ajk", "R_LWR");
	//����ʱ������
	map.insert("akh", "SnShnHrRd");
	//����ʱ��
	map.insert("akc", "SnShnHr");
	//��ѹ
	map.insert("aga", "StationPressure");
	//��ѹ���ֵ
	map.insert("agaa", "MaxPrs");
	//��ѹ���ֵ����ʱ��
	map.insert("agab", "MaxPrsDT");
	//��ѹ��Сֵ
	map.insert("agac", "MinPrs");
	//��ѹ��Сֵ����ʱ��
	map.insert("agad", "MinPrsDT");
	//�����ӷ���
	map.insert("aec1", "WD_Avg2MWD");
	//�����ӷ���
	map.insert("afc1", "WS_Avg2MWS1");
	//ʮ���ӷ���
	map.insert("aed1", "WD_Avg10MWD");
	//ʮ���ӷ���
	map.insert("afd1", "WS_Avg10MWS1");
	//�����ٵķ���
	map.insert("aeg1", "WD_MaxWSD");
	//������
	map.insert("afd1a", "WS_MaxWS1");
	//�����ٳ���ʱ��
	map.insert("afd1d", "WS_MaxWS1T");
	//��ǰʱ�̵�˲ʱ����
	map.insert("aea1", "WD_IWD");
	//��ǰʱ�̵�˲ʱ����
	map.insert("afa1", "WS_IWS1");
	//1����˲ʱ�����ٶ�Ӧ����
	map.insert("aef1", "WD_Max1MIWSD");
	//����˲ʱ������
	map.insert("afa1a", "WS_Max1MWS1");
	//������ٵķ���
	map.insert("aee1", "WD_EWSD");
	//�������
	map.insert("afa1e", "WS_EWS1");
	//�������ʱ��
	map.insert("afa1f", "WS_EWS1T");
	//�豸״̬Ҫ��
	//�豸�Լ�״̬
	map.insert("z", "AutoCheckSts1");
	//����ֲ��Լ�״̬
	map.insert("z_aa", "WeatherSelfCheck");
	//���·ֲ��Լ�״̬
	map.insert("z_ab", "SoilTmpSelfCheck");
	//��ʪ�ֲ��Լ�״̬
	map.insert("z_ad", "TempHSelfCheck");
	//����ֲ��Լ�״̬
	map.insert("z_aj", "RadarSelfCheck");
	//����ˮ�ֲַ��Լ�״̬
	map.insert("z_ar", "SoilMoistSelfCheck");

	//1.5�����´�����״̬
	map.insert("y_aaa", "AirTmprtSensorSts1");
	//5cm���´�����״̬
	map.insert("y_ab5", "SoilTmprtSensorSts1");
	//ǳ��10cm���´������Ĺ���״̬
	map.insert("y_ab10", "SoilTmprtSensorSts2");
	//ǳ��15cm���´������Ĺ���״̬
	map.insert("y_ab15", "SoilTmprtSensorSts3");
	//ǳ��20cm���´������Ĺ���״̬
	map.insert("y_ab20", "SoilTmprtSensorSts4");
	//���40cm���´������Ĺ���״̬
	map.insert("y_ab40", "SoilTmprtSensorSts5");
	//���80cm���´������Ĺ���״̬
	map.insert("y_ab80", "SoilTmprtSensorSts6");
	//���160cm���´������Ĺ���״̬
	map.insert("y_ab160", "SoilTmprtSensorSts7");
	//���320cm���´������Ĺ���״̬
	map.insert("y_ab320", "SoilTmprtSensorSts8");

	//Һ���´������Ĺ���״̬
	map.insert("y_aca", "LiquidTempSts");
	//�����¶ȴ������Ĺ���״̬
	map.insert("y_acb", "FreezTempSts");
	//���ʪ�ȴ������Ĺ���״̬
	map.insert("y_ada", "AirHmdSensorSts1");
	//���򴫸����Ĺ���״̬
	map.insert("y_aea", "WndDrctSensorSts");
	//���ٴ������Ĺ���״̬
	map.insert("y_afa", "WndSpdSensorSts1");
	//��ѹ�������Ĺ���״̬
	map.insert("y_aga", "PressSts");
	//����������(�ǳ��ط�ʽ)�Ĺ���״̬
	map.insert("y_aha", "RnflSensorSts");
	//�ܷ���������Ĺ���״̬
	map.insert("y_aja", "TotalRdSensorSts");
	//�����Ч����������Ĺ���״̬
	map.insert("y_aji", "PhticEfcnySensorSts");
	//���մ������Ĺ���״̬
	map.insert("y_aka", "SunShnSts");
	//�ƴ������Ĺ���״̬
	//map.insert("y_ala","CloudHSts");
	//�ܼ����ǵĹ���״̬
	map.insert("y_ama", "VisiSts");
	//���������ǵĹ���״̬
	map.insert("y_ana", "WheathSts");
	//·��״���������Ĺ���״̬
	map.insert("y_aqa", "RoadSts");
	//0-10cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara10", "SoilHmdSensorSts1");
	//10-20cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara20", "SoilHmdSensorSts2");
	//20-30cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara30", "SoilHmdSensorSts3");
	//30-40cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara40", "SoilHmdSensorSts4");
	//40-50cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara50", "SoilHmdSensorSts5");
	//50-60cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara60", "SoilHmdSensorSts6");
	//60-70cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara70", "SoilHmdSensorSts7");
	//70-80cm����ˮ�ִ������Ĺ���״̬
	map.insert("y_ara80", "SoilHmdSensorSts8");

	//��ӵ�Դ�������豸�����ɼ�������Ҫ��׺��
	map.insert("xa", "ExtPwrSts1");
	//����ֲ���ӵ�Դ״̬
	map.insert("xa_aa", "WeatherExpPower");
	//���·ֲ���ӵ�Դ״̬
	map.insert("xa_ab", "SoilTempExpPower");
	//��ʪ�ֲ���ӵ�Դ״̬
	map.insert("xa_ad", "TempHExpPower");
	//����ֲ���ӵ�Դ״̬
	map.insert("xa_aj", "RadarExpPower");
	//����ˮ�ֲַ���ӵ�Դ״̬
	map.insert("xa_ar", "SoilMonisExpPower");
	//�豸/���������ѹ״̬
	map.insert("xb", "MainClctrVltgSts");
	//���ص�ѹ״̬
	map.insert("xd", "BtryVltgSts1");
	//AC-DC��ѹ״̬
	map.insert("xe", "ADDCVltgSts1");
	//��ת��̨������ѹ״̬
	map.insert("xg", "PTZPower");
	//̫���ܵ�ذ�״̬
	map.insert("xi", "SolarPanelSts");
	//�豸/�������廷���¶�״̬
	map.insert("wa", "MotherTemp");
	//���·ֲɵ������¶�״̬
	map.insert("wa_aa", "WeathTemp");
	//���·ֲɵ������¶�״̬
	map.insert("wa_ab", "SoilTemp");
	//��ʪ�ֲɵ������¶�״̬
	map.insert("wa_ad", "THTemp");
	//����ֲɵ������¶�״̬
	map.insert("wa_aj", "RadarTemp");
	//����ˮ�ֲַɵ������¶�״̬
	map.insert("wa_ar", "SMTemp");
	//̽�����¶�״̬
	map.insert("wb", "TTemp");
	//ǻ���¶�״̬
	map.insert("wc", "QTemp");
	//�ܷ����ǻ���¶�״̬
	map.insert("wc_aja", "ZRQTemp");
	//��������ǻ���¶�״̬
	map.insert("wc_ajb", "FQTemp");
	//ֱ�ӷ����ǻ���¶�״̬
	map.insert("wc_ajc", "ZQTemp");
	//ɢ������ǻ���¶�״̬
	map.insert("wc_ajd", "SQTemp");
	//�������ǻ���¶�״̬
	map.insert("wc_aje", "JQTemp");
	//���⣨A+B�������ǻ���¶�״̬
	map.insert("wc_ajf", "ZABTemp");
	//����A�����ǻ���¶�״̬
	map.insert("wc_ajg", "ZATemp");
	//����B�����ǻ���¶�״̬
	map.insert("wc_ajh", "ZBTemp");
	//�����Ч�����ǻ���¶�״̬
	map.insert("wc_aji", "GTemp");
	//�������������ǻ���¶�״̬
	map.insert("wc_ajj", "ATemp");
	//���泤�������ǻ���¶�״̬
	map.insert("wc_ajk", "SLRTemp");

	//�������¶�״̬
	map.insert("wd", "ThermTemp");
	//�ܷ����������¶�״̬
	map.insert("wd_aja", "TRTTemp");
	//��������������¶�״̬
	map.insert("wd_ajb", "FRTTemp");
	//ֱ�ӷ����������¶�״̬
	map.insert("wd_ajc", "ZRTTemp");
	//ɢ������������¶�״̬
	map.insert("wd_ajd", "SRTTemp");
	//�������������¶�״̬
	map.insert("wd_aje", "JRTTemp");
	//���⣨A+B�������������¶�״̬
	map.insert("wd_ajf", "ZABRTTemp");
	//����A�����������¶�״̬
	map.insert("wd_ajg", "ZARTTemp");
	//����B�����������¶�״̬
	map.insert("wd_ajh", "ZBRTTemp");
	//�����Ч�����������¶�״̬
	map.insert("wd_aji", "GRTTemp");
	//�������������������¶�״̬
	map.insert("wd_ajj", "ALRTemp");
	//���泤�������������¶�״̬
	map.insert("wd_ajk", "SLRTTemp");
	//�����¶�״̬
	map.insert("we", "ChassisTemp");
	//�豸����
	map.insert("va", "DeviceHeat");
	//����������
	map.insert("vb", "SendHeat1");
	//����������
	map.insert("vc", "RecvHeat1");
	//�������
	map.insert("vd", "PhoneHeat");
	//���������
	map.insert("ve", "CamaraHeat");
	//�豸ͨ��״̬
	map.insert("ua", "DeviceVent");
	//������ͨ��״̬
	map.insert("ub", "SendVent1");
	//������ͨ��״̬
	map.insert("uc", "RecvVent1");
	//ͨ����ͨ��״̬
	map.insert("ud", "VentV");
	//���¹۲�ͨ�����ٶ�
	map.insert("ud_aaa", "AVVent");
	//�ܷ����ͨ��״̬
	map.insert("ue_aja", "TRVent");
	//��������ͨ��״̬
	map.insert("ue_ajb", "FRVent");
	//ֱ�ӷ����ͨ��״̬
	map.insert("ue_ajc", "ZRVent");
	//ɢ������ͨ��״̬
	map.insert("ue_ajd", "SRVent");
	//�������ͨ��״̬
	map.insert("ue_aje", "JRVent");
	//���⣨A+B�������ͨ��״̬
	map.insert("ue_ajf", "ZABVent");
	//����A�����ͨ��״̬
	map.insert("ue_ajg", "ZARVent");
	//����B�����ͨ��״̬
	map.insert("ue_ajh", "ZBRVent");
	//�����Ч�����ͨ��״̬
	map.insert("ue_aji", "GRVent");
	//�������������ͨ��״̬
	map.insert("ue_ajj", "ALRVent");
	//���泤�������ͨ��״̬
	map.insert("ue_ajk", "SLRVent");
	//�豸�����ɣ������ڷ�������PC�ն����ӵ�ͨ��״̬
	map.insert("ta", "PCConnet");
	//����״̬���豸��ֲɻ��������ܴ�����������״ָ̬ʾ
	map.insert("tb", "BusStatus");
	//RS232/485/422״̬
	map.insert("tc", "RSStatus");
	//���·ֲɵ�RS232/485/422״̬
	map.insert("tc_aa", "WStatus");
	//���·ֲɵ�RS232/485/422״̬
	map.insert("tc_ab", "SWStatus");
	//��ʪ�ֲɵ�RS232/485/422״̬
	map.insert("tc_ad", "THStatus");
	//����ֲɵ�RS232/485/422״̬
	map.insert("tc_aj", "RStatus");
	//����ˮ�ֲַɵ�RS232/485/422״̬
	map.insert("tc_ar", "SMStatus");
	//RJ45/LANͨ��״̬
	map.insert("td", "RJStatus");
	//����ͨ��״̬
	map.insert("te", "SateStatus");
	//����ͨ��״̬
	map.insert("tf", "WireLessStatus");
	//����ͨ��״̬
	map.insert("tg", "RateStatus");
	//������Ⱦ���
	map.insert("sa", "WPStatus1");
	//̽������Ⱦ���
	map.insert("sb", "TPStatus");
	//�����ͷ��Ⱦ���
	map.insert("sc", "PhPStatus");
	//�������ͷ��Ⱦ���
	map.insert("sd", "CPStatus");
	//������״̬
	map.insert("rb", "RecevierSts1");
	//������״̬
	map.insert("rc", "SenderSts1");
	//��ת��̨����״��
	map.insert("re", "PTZWorkSts");
	//���������״��
	map.insert("rf", "CamaWorkSts");
	//�������״��
	map.insert("rg", "PhotoWorkSts");
	//�ɼ�������״̬
	map.insert("ri", "CollectOperSts");
	//AD״̬
	map.insert("rj", "MainClctrADSts");
	//������״̬
	map.insert("rk", "MainClctrCntSts");
	//��״̬
	map.insert("rl", "DoorSts");
	//��ˮ״̬
	map.insert("rm", "IntoWaterSts");
	//��λ״̬
	map.insert("rn", "ShiftSts");
	//ˮλ״̬
	map.insert("rp", "WaterLevelSts");
	//��洢��״̬
	map.insert("rq", "ExCardSts");
}

QString Dictionary::Find(QString key)
{
	QMap<QString, QString>::const_iterator mi = map.find(key);
	if (mi != map.end())
		return map[key];
	return NULL;
}
