#include "dictionary.h"

Dictionary::Dictionary()
{
	//观察要素
	//两分钟风向
	map.insert("aec", "WD_Avg2MWD");
	//两分钟风速
	map.insert("afc", "WS_Avg2MWS1");
	//十分钟风向
	map.insert("aed", "WD_Avg10MWD");
	//十分钟风速+——
	map.insert("afd", "WS_Avg10MWS1");
	//最大风速风向
	map.insert("aeg", "WD_MaxWSD");
	//最大风速
	map.insert("afda", "WS_MaxWS1");
	//最大风速出现时间
	map.insert("afdb", "WS_MaxWS1T");
	//当前时刻瞬时风向
	map.insert("aea", "WD_IWD");
	//当前时刻瞬时风速
	map.insert("afa", "WS_IWS1");
	//1分钟内瞬时最大风速风向
	map.insert("aef", "WD_Max1MIWSD");
	//1分钟内瞬时最大风速
	map.insert("afaa", "WS_Max1MWS1");
	//极大风速风向
	map.insert("aee", "WD_EWSD");
	//极大风速
	map.insert("afae", "WS_EWS1");
	//极大风速出现时间
	map.insert("afaf", "WS_EWS1T");

	//第一层气温
	map.insert("aaa", "AT_AT1");
	//第一层气温最大值
	map.insert("aaaa", "AT_MaxAT1");
	//第一层气温最大值出现时间
	map.insert("aaab", "AT_MaxAT1T");
	//第一层气温最小值
	map.insert("aaac", "AT_MinAT1");
	//第一层气温最小值出现时间
	map.insert("aaad", "AT_MinAT1T");
	//第一层湿度
	map.insert("ada", "AH_RH1");
	//第一层湿度最小值
	map.insert("adac", "AH_MinRH1");
	//第一层湿度最小值出现时间
	map.insert("adad", "AH_MinRH1T");
	//第一层水汽压
	map.insert("adc", "AH_WVP1");
	//第一层露点温度
	map.insert("adb", "AH_DPT1");

	//第二层气温
	map.insert("aaa1", "AT_AT2");
	//第二层气温最大值
	map.insert("aaa1a", "AT_MaxAT2");
	//第二层气温最大值出现时间
	map.insert("aaa1b", "AT_MaxAT2T");
	//第二层气温最小值
	map.insert("aaa1c", "AT_MinAT2");
	//第二层气温最小值出现时间
	map.insert("aaa1d", "AT_MinAT2T");
	//第二层湿度
	map.insert("ada1", "AH_RH2");
	//第二层湿度最小值
	map.insert("ada1c", "AH_MinRH2");
	//第二层湿度最小值出现时间
	map.insert("ada1d", "AH_MinRH2T");
	//第二层水汽压
	map.insert("adc1", "AH_WVP2");
	//第二层露点温度
	map.insert("adb1", "AH_DPT2");

	//第三层气温
	map.insert("aaa2", "AT_AT3");
	//第三层气温最大值
	map.insert("aaa2a", "AT_MaxAT3");
	//第三层气温最大值出现时间
	map.insert("aaa2b", "AT_MaxAT3T");
	//第三层气温最小值
	map.insert("aaa2c", "AT_MinAT3");
	//第三层气温最小值出现时间
	map.insert("aaa2d", "AT_MinAT3T");
	//第三层湿度
	map.insert("ada2", "AH_RH3");
	//第三层湿度最小值
	map.insert("ada2c", "AH_MinRH3");
	//第三层湿度最小值出现时间
	map.insert("ada2d", "AH_MinRH3T");
	//第三层水汽压
	map.insert("adc2", "AH_WVP3");
	//第三层露点温度
	map.insert("adb2", "AH_DPT3");

	//第四层气温
	map.insert("aaa3", "AT_AT4");
	//第四层气温最大值
	map.insert("aaa3a", "AT_MaxAT4");


	//第四层气温最大值出现时间
	map.insert("aaa3b", "AT_MaxAT4T");
	//第四层气温最小值
	map.insert("aaa3c", "AT_MinAT4");
	//第四层气温最小值出现时间
	map.insert("aaa3d", "AT_MinAT4T");
	//第四层湿度
	map.insert("ada3", "AH_RH4");
	//第四层湿度最小值
	map.insert("ada3c", "AH_MinRH4");
	//第四层湿度最小值出现时间
	map.insert("ada3d", "AH_MinRH4T");
	//第四层水汽压
	map.insert("adc3", "AH_WVP4");
	//第四层露点温度
	map.insert("adb3", "AH_DPT4");

	//第一层地温
	map.insert("ab5", "ST_ST1");
	//第一层地温最大值
	map.insert("ab5a", "ST_MaxST1");
	//第一层地温最大值出现时间
	map.insert("ab5b", "ST_MaxST1T");
	//第一层地温最小值
	map.insert("ab5c", "ST_MinST1");
	//第一层地温最小值出现时间
	map.insert("ab5d", "ST_MinST1T");

	//第二层地温
	map.insert("ab10", "ST_ST2");
	//第二层地温最大值
	map.insert("ab10a", "ST_MaxST2");
	//第二层地温最大值出现时间
	map.insert("ab10b", "ST_MaxST2T");
	//第二层地温最小值
	map.insert("ab10c", "ST_MinST2");
	//第二层地温最小值出现时间
	map.insert("ab10d", "ST_MinST2T");

	//第三层地温
	map.insert("ab15", "ST_ST3");
	//第三层地温最大值
	map.insert("ab15a", "ST_MaxST3");
	//第三层地温最大值出现时间
	map.insert("ab15b", "ST_MaxST3T");
	//第三层地温最小值
	map.insert("ab15c", "ST_MinST3");
	//第三层地温最小值出现时间
	map.insert("ab15d", "ST_MinST3T");

	//第四层地温
	map.insert("ab20", "ST_ST4");
	//第四层地温最大值
	map.insert("ab20a", "ST_MaxST4");
	//第四层地温最大值出现时间
	map.insert("ab20b", "ST_MaxST4T");
	//第四层地温最小值
	map.insert("ab20c", "ST_MinST4");
	//第四层地温最小值出现时间
	map.insert("ab20d", "ST_MinST4T");

	//第五层地温
	map.insert("ab30", "ST_ST5");
	//第五层地温最大值
	map.insert("ab30a", "ST_MaxST5");
	//第五层地温最大值出现时间
	map.insert("ab30b", "ST_MaxST5T");
	//第五层地温最小值
	map.insert("ab30c", "ST_MinST5");
	//第五层地温最小值出现时间
	map.insert("ab30d", "ST_MinST5T");

	//第六层地温
	map.insert("ab40", "ST_ST6");
	//第六层地温最大值
	map.insert("ab40a", "ST_MaxST6");
	//第六层地温最大值出现时间
	map.insert("ab40b", "ST_MaxST6T");
	//第六层地温最小值
	map.insert("ab40c", "ST_MinST6");
	//第六层地温最小值出现时间
	map.insert("ab40d", "ST_MinST6T");

	//第七层地温
	map.insert("ab50", "ST_ST7");
	//第七层地温最大值
	map.insert("ab50a", "ST_MaxST7");
	//第七层地温最大值出现时间
	map.insert("ab50b", "ST_MaxST7T");
	//第七层地温最小值
	map.insert("ab50c", "ST_MinST7");
	//第七层地温最小值出现时间
	map.insert("ab50d", "ST_MinST7T");

	//第八层地温
	map.insert("ab50", "ST_ST8");
	//第八层地温最大值
	map.insert("ab50a", "ST_MaxST8");
	//第八层地温最大值出现时间
	map.insert("ab50b", "ST_MaxST8T");
	//第八层地温最小值
	map.insert("ab50c", "ST_MinST8");
	//第八层地温最小值出现时间
	map.insert("ab50d", "ST_MinST8T");

	//裸温1（草面温度）
	map.insert("aba", "OT_GT");
	//红外温度
	map.insert("aab", "OT_IT");
	//总辐射
	map.insert("aja", "R_TRI");
	//总辐射曝辐量
	map.insert("ajaa", "R_TRD");
	//总辐射照度最大值
	map.insert("ajae", "R_MaxMTRI");
	//光合有效
	map.insert("aji", "R_PERI");
	//光合有效辐射曝辐量
	map.insert("ajia", "R_PERD");
	//CO2浓度
	map.insert("asa", "CO2IC");
	//CO2浓度最大值
	map.insert("asaa", "MaxCO2C");
	//CO2浓度最大值出现时间
	map.insert("asab", "MaxCO2CT");
	//CO2浓度最小值
	map.insert("asac", "MinCO2Cntr");
	//CO2浓度最小值出现时间
	map.insert("asad", "MinDayCO2CT");
	//蒸发
	map.insert("aia", "Evaporat");
	//净辐射
	map.insert("aje", "R_CR");
	//反射辐射
	map.insert("ajb", "R_RR");
	//紫外线辐射
	map.insert("ajg", "R_UR");
	//地面长波辐射
	map.insert("ajk", "R_LWR");
	//日照时数辐射
	map.insert("akh", "SnShnHrRd");
	//日照时数
	map.insert("akc", "SnShnHr");
	//气压
	map.insert("aga", "StationPressure");
	//气压最大值
	map.insert("agaa", "MaxPrs");
	//气压最大值出现时间
	map.insert("agab", "MaxPrsDT");
	//气压最小值
	map.insert("agac", "MinPrs");
	//气压最小值出现时间
	map.insert("agad", "MinPrsDT");
	//两分钟风向
	map.insert("aec1", "WD_Avg2MWD");
	//两分钟风速
	map.insert("afc1", "WS_Avg2MWS1");
	//十分钟风向
	map.insert("aed1", "WD_Avg10MWD");
	//十分钟风速
	map.insert("afd1", "WS_Avg10MWS1");
	//最大风速的风向
	map.insert("aeg1", "WD_MaxWSD");
	//最大风速
	map.insert("afd1a", "WS_MaxWS1");
	//最大风速出现时间
	map.insert("afd1d", "WS_MaxWS1T");
	//当前时刻的瞬时风向
	map.insert("aea1", "WD_IWD");
	//当前时刻的瞬时风速
	map.insert("afa1", "WS_IWS1");
	//1分钟瞬时最大风速对应风向
	map.insert("aef1", "WD_Max1MIWSD");
	//分钟瞬时最大风速
	map.insert("afa1a", "WS_Max1MWS1");
	//极大风速的风向
	map.insert("aee1", "WD_EWSD");
	//极大风速
	map.insert("afa1e", "WS_EWS1");
	//极大风速时间
	map.insert("afa1f", "WS_EWS1T");
	//设备状态要素
	//设备自检状态
	map.insert("z", "AutoCheckSts1");
	//气候分采自检状态
	map.insert("z_aa", "WeatherSelfCheck");
	//地温分采自检状态
	map.insert("z_ab", "SoilTmpSelfCheck");
	//温湿分采自检状态
	map.insert("z_ad", "TempHSelfCheck");
	//辐射分采自检状态
	map.insert("z_aj", "RadarSelfCheck");
	//土壤水分分采自检状态
	map.insert("z_ar", "SoilMoistSelfCheck");

	//1.5米气温传感器状态
	map.insert("y_aaa", "AirTmprtSensorSts1");
	//5cm地温传感器状态
	map.insert("y_ab5", "SoilTmprtSensorSts1");
	//浅层10cm地温传感器的工作状态
	map.insert("y_ab10", "SoilTmprtSensorSts2");
	//浅层15cm地温传感器的工作状态
	map.insert("y_ab15", "SoilTmprtSensorSts3");
	//浅层20cm地温传感器的工作状态
	map.insert("y_ab20", "SoilTmprtSensorSts4");
	//深层40cm地温传感器的工作状态
	map.insert("y_ab40", "SoilTmprtSensorSts5");
	//深层80cm地温传感器的工作状态
	map.insert("y_ab80", "SoilTmprtSensorSts6");
	//深层160cm地温传感器的工作状态
	map.insert("y_ab160", "SoilTmprtSensorSts7");
	//深层320cm地温传感器的工作状态
	map.insert("y_ab320", "SoilTmprtSensorSts8");

	//液面温传感器的工作状态
	map.insert("y_aca", "LiquidTempSts");
	//冰点温度传感器的工作状态
	map.insert("y_acb", "FreezTempSts");
	//相对湿度传感器的工作状态
	map.insert("y_ada", "AirHmdSensorSts1");
	//风向传感器的工作状态
	map.insert("y_aea", "WndDrctSensorSts");
	//风速传感器的工作状态
	map.insert("y_afa", "WndSpdSensorSts1");
	//气压传感器的工作状态
	map.insert("y_aga", "PressSts");
	//雨量传感器(非称重方式)的工作状态
	map.insert("y_aha", "RnflSensorSts");
	//总辐射表传感器的工作状态
	map.insert("y_aja", "TotalRdSensorSts");
	//光合有效辐射表传感器的工作状态
	map.insert("y_aji", "PhticEfcnySensorSts");
	//日照传感器的工作状态
	map.insert("y_aka", "SunShnSts");
	//云传感器的工作状态
	//map.insert("y_ala","CloudHSts");
	//能见度仪的工作状态
	map.insert("y_ama", "VisiSts");
	//天气现象仪的工作状态
	map.insert("y_ana", "WheathSts");
	//路面状况传感器的工作状态
	map.insert("y_aqa", "RoadSts");
	//0-10cm土壤水分传感器的工作状态
	map.insert("y_ara10", "SoilHmdSensorSts1");
	//10-20cm土壤水分传感器的工作状态
	map.insert("y_ara20", "SoilHmdSensorSts2");
	//20-30cm土壤水分传感器的工作状态
	map.insert("y_ara30", "SoilHmdSensorSts3");
	//30-40cm土壤水分传感器的工作状态
	map.insert("y_ara40", "SoilHmdSensorSts4");
	//40-50cm土壤水分传感器的工作状态
	map.insert("y_ara50", "SoilHmdSensorSts5");
	//50-60cm土壤水分传感器的工作状态
	map.insert("y_ara60", "SoilHmdSensorSts6");
	//60-70cm土壤水分传感器的工作状态
	map.insert("y_ara70", "SoilHmdSensorSts7");
	//70-80cm土壤水分传感器的工作状态
	map.insert("y_ara80", "SoilHmdSensorSts8");

	//外接电源（独立设备或主采集器不需要后缀）
	map.insert("xa", "ExtPwrSts1");
	//气候分采外接电源状态
	map.insert("xa_aa", "WeatherExpPower");
	//地温分采外接电源状态
	map.insert("xa_ab", "SoilTempExpPower");
	//温湿分采外接电源状态
	map.insert("xa_ad", "TempHExpPower");
	//辐射分采外接电源状态
	map.insert("xa_aj", "RadarExpPower");
	//土壤水分分采外接电源状态
	map.insert("xa_ar", "SoilMonisExpPower");
	//设备/主采主板电压状态
	map.insert("xb", "MainClctrVltgSts");
	//蓄电池电压状态
	map.insert("xd", "BtryVltgSts1");
	//AC-DC电压状态
	map.insert("xe", "ADDCVltgSts1");
	//旋转云台工作电压状态
	map.insert("xg", "PTZPower");
	//太阳能电池板状态
	map.insert("xi", "SolarPanelSts");
	//设备/主采主板环境温度状态
	map.insert("wa", "MotherTemp");
	//气温分采的主板温度状态
	map.insert("wa_aa", "WeathTemp");
	//地温分采的主板温度状态
	map.insert("wa_ab", "SoilTemp");
	//温湿分采的主板温度状态
	map.insert("wa_ad", "THTemp");
	//辐射分采的主板温度状态
	map.insert("wa_aj", "RadarTemp");
	//土壤水分分采的主板温度状态
	map.insert("wa_ar", "SMTemp");
	//探测器温度状态
	map.insert("wb", "TTemp");
	//腔体温度状态
	map.insert("wc", "QTemp");
	//总辐射表腔体温度状态
	map.insert("wc_aja", "ZRQTemp");
	//反射辐射表腔体温度状态
	map.insert("wc_ajb", "FQTemp");
	//直接辐射表腔体温度状态
	map.insert("wc_ajc", "ZQTemp");
	//散射辐射表腔体温度状态
	map.insert("wc_ajd", "SQTemp");
	//净辐射表腔体温度状态
	map.insert("wc_aje", "JQTemp");
	//紫外（A+B）辐射表腔体温度状态
	map.insert("wc_ajf", "ZABTemp");
	//紫外A辐射表腔体温度状态
	map.insert("wc_ajg", "ZATemp");
	//紫外B辐射表腔体温度状态
	map.insert("wc_ajh", "ZBTemp");
	//光合有效辐射表腔体温度状态
	map.insert("wc_aji", "GTemp");
	//大气长波辐射表腔体温度状态
	map.insert("wc_ajj", "ATemp");
	//地面长波辐射表腔体温度状态
	map.insert("wc_ajk", "SLRTemp");

	//恒温器温度状态
	map.insert("wd", "ThermTemp");
	//总辐射表恒温器温度状态
	map.insert("wd_aja", "TRTTemp");
	//反射辐射表恒温器温度状态
	map.insert("wd_ajb", "FRTTemp");
	//直接辐射表恒温器温度状态
	map.insert("wd_ajc", "ZRTTemp");
	//散射辐射表恒温器温度状态
	map.insert("wd_ajd", "SRTTemp");
	//净辐射表恒温器温度状态
	map.insert("wd_aje", "JRTTemp");
	//紫外（A+B）辐射表恒温器温度状态
	map.insert("wd_ajf", "ZABRTTemp");
	//紫外A辐射表恒温器温度状态
	map.insert("wd_ajg", "ZARTTemp");
	//紫外B辐射表恒温器温度状态
	map.insert("wd_ajh", "ZBRTTemp");
	//光合有效辐射表恒温器温度状态
	map.insert("wd_aji", "GRTTemp");
	//大气长波辐射表恒温器温度状态
	map.insert("wd_ajj", "ALRTemp");
	//地面长波辐射表恒温器温度状态
	map.insert("wd_ajk", "SLRTTemp");
	//机箱温度状态
	map.insert("we", "ChassisTemp");
	//设备加热
	map.insert("va", "DeviceHeat");
	//发射器加热
	map.insert("vb", "SendHeat1");
	//接收器加热
	map.insert("vc", "RecvHeat1");
	//相机加热
	map.insert("vd", "PhoneHeat");
	//摄像机加热
	map.insert("ve", "CamaraHeat");
	//设备通风状态
	map.insert("ua", "DeviceVent");
	//发射器通风状态
	map.insert("ub", "SendVent1");
	//接收器通风状态
	map.insert("uc", "RecvVent1");
	//通风罩通风状态
	map.insert("ud", "VentV");
	//气温观测通风罩速度
	map.insert("ud_aaa", "AVVent");
	//总辐射表通风状态
	map.insert("ue_aja", "TRVent");
	//反射辐射表通风状态
	map.insert("ue_ajb", "FRVent");
	//直接辐射表通风状态
	map.insert("ue_ajc", "ZRVent");
	//散射辐射表通风状态
	map.insert("ue_ajd", "SRVent");
	//净辐射表通风状态
	map.insert("ue_aje", "JRVent");
	//紫外（A+B）辐射表通风状态
	map.insert("ue_ajf", "ZABVent");
	//紫外A辐射表通风状态
	map.insert("ue_ajg", "ZARVent");
	//紫外B辐射表通风状态
	map.insert("ue_ajh", "ZBRVent");
	//光合有效辐射表通风状态
	map.insert("ue_aji", "GRVent");
	//大气长波辐射表通风状态
	map.insert("ue_ajj", "ALRVent");
	//地面长波辐射表通风状态
	map.insert("ue_ajk", "SLRVent");
	//设备（主采）到串口服务器或PC终端连接的通信状态
	map.insert("ta", "PCConnet");
	//总线状态（设备与分采或其他智能传感器的总线状态指示
	map.insert("tb", "BusStatus");
	//RS232/485/422状态
	map.insert("tc", "RSStatus");
	//气温分采的RS232/485/422状态
	map.insert("tc_aa", "WStatus");
	//地温分采的RS232/485/422状态
	map.insert("tc_ab", "SWStatus");
	//温湿分采的RS232/485/422状态
	map.insert("tc_ad", "THStatus");
	//辐射分采的RS232/485/422状态
	map.insert("tc_aj", "RStatus");
	//土壤水分分采的RS232/485/422状态
	map.insert("tc_ar", "SMStatus");
	//RJ45/LAN通信状态
	map.insert("td", "RJStatus");
	//卫星通信状态
	map.insert("te", "SateStatus");
	//无线通信状态
	map.insert("tf", "WireLessStatus");
	//光纤通信状态
	map.insert("tg", "RateStatus");
	//窗口污染情况
	map.insert("sa", "WPStatus1");
	//探测器污染情况
	map.insert("sb", "TPStatus");
	//相机镜头污染情况
	map.insert("sc", "PhPStatus");
	//摄像机镜头污染情况
	map.insert("sd", "CPStatus");
	//接收器状态
	map.insert("rb", "RecevierSts1");
	//发射器状态
	map.insert("rc", "SenderSts1");
	//旋转云台工作状况
	map.insert("re", "PTZWorkSts");
	//摄像机工作状况
	map.insert("rf", "CamaWorkSts");
	//相机工作状况
	map.insert("rg", "PhotoWorkSts");
	//采集器运行状态
	map.insert("ri", "CollectOperSts");
	//AD状态
	map.insert("rj", "MainClctrADSts");
	//计数器状态
	map.insert("rk", "MainClctrCntSts");
	//门状态
	map.insert("rl", "DoorSts");
	//进水状态
	map.insert("rm", "IntoWaterSts");
	//移位状态
	map.insert("rn", "ShiftSts");
	//水位状态
	map.insert("rp", "WaterLevelSts");
	//外存储卡状态
	map.insert("rq", "ExCardSts");
}

QString Dictionary::Find(QString key)
{
	QMap<QString, QString>::const_iterator mi = map.find(key);
	if (mi != map.end())
		return map[key];
	return NULL;
}
