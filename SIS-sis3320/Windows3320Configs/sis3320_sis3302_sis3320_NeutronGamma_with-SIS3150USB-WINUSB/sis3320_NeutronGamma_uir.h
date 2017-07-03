/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2009. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  CLOCK_CONF                      1
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_8   2       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_7   3       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_6   4       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_5   5       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_4   6       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_3   7       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_2   8       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G2_1   9       /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_8   10      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_7   11      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_6   12      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_5   13      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_4   14      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_TEXTMSG_2            15
#define  CLOCK_CONF_TEXTMSG              16
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_3   17      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_2   18      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_G1_1   19      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CURSORMSG_56         20
#define  CLOCK_CONF_CHECKBOX_FLAG_G_AND  21      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_CTRL2  22      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_CTRL3  23      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_TRIGGER 24     /* callback function: CB_SIS3320_ExternalConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_TIMSTAM 25     /* callback function: CB_SIS3320_ExternalConfFlags */
#define  CLOCK_CONF_CHECKBOX_FLAG_CTRL4  26      /* callback function: CB_ClockConfFlags */
#define  CLOCK_CONF_CURSORMSG_CLOCK      27
#define  CLOCK_CONF_CURSORMSG_53         28
#define  CLOCK_CONF_SIS3320_TRIGGER_MODE 29      /* callback function: CB_SIS3320_TriggerMode_Souce_Conf */
#define  CLOCK_CONF_SIS3302_MODE_CLK     30      /* callback function: CB_ClockModeConf */
#define  CLOCK_CONF_SIS3320_MODE_CLK     31      /* callback function: CB_ClockModeConf */
#define  CLOCK_CONF_SIS3820_MODE_CLK_E2  32      /* callback function: CB_ClockModeConf */
#define  CLOCK_CONF_SIS3820_MODE_CLK     33      /* callback function: CB_ClockModeConf */
#define  CLOCK_CONF_CURSORMSG_55         34
#define  CLOCK_CONF_DECORATION_20        35
#define  CLOCK_CONF_DECORATION_19        36
#define  CLOCK_CONF_DECORATION_18        37

#define  DAC_CONF                        2
#define  DAC_CONF_DAC_OFFSET_ADC7        2       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC8        3       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC6        4       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC5        5       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC4        6       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC3        7       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC2        8       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DAC_OFFSET_ADC1        9       /* callback function: CB_DacOffsetConf */
#define  DAC_CONF_DECORATION_17          10
#define  DAC_CONF_CURSORMSG_5            11
#define  DAC_CONF_ADC_VALUE_TABLE        12
#define  DAC_CONF_DAC_OFFSET_TABLE       13
#define  DAC_CONF_LED_LOOP               14

#define  GAIN_CONF                       3
#define  GAIN_CONF_CURSORMSG_14          2
#define  GAIN_CONF_CURSORMSG_15          3
#define  GAIN_CONF_CURSORMSG_16          4
#define  GAIN_CONF_CURSORMSG_17          5
#define  GAIN_CONF_CURSORMSG_9           6
#define  GAIN_CONF_CURSORMSG_8           7
#define  GAIN_CONF_CURSORMSG_7           8
#define  GAIN_CONF_CURSORMSG_41          9
#define  GAIN_CONF_CURSORMSG_38          10
#define  GAIN_CONF_DECORATION_17         11
#define  GAIN_CONF_CHECK_HALFSCALE_ADC8  12      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC7  13      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC6  14      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC5  15      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC4  16      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC3  17      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC2  18      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_CHECK_HALFSCALE_ADC1  19      /* callback function: CB_Gain_Flags */
#define  GAIN_CONF_GAIN_TABLE            20
#define  GAIN_CONF_CURSORMSG_42          21
#define  GAIN_CONF_CURSORMSG_5           22

#define  HELP_GATE                       4
#define  HELP_GATE_PICTURE               2

#define  MESS_ERR                        5
#define  MESS_ERR_TEXTBOX                2

#define  MESS_SYS                        6
#define  MESS_SYS_TEXTBOX                2

#define  MOD_CONF                        7
#define  MOD_CONF_CLOCK_MODULE_ADDR      2       /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_32           3
#define  MOD_CONF_CURSORMSG_31           4
#define  MOD_CONF_CURSORMSG_28           5
#define  MOD_CONF_MODULE_ADDR_14         6       /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_38           7
#define  MOD_CONF_MODULE_ADDR_13         8       /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_37           9
#define  MOD_CONF_MODULE_ADDR_12         10      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_36           11
#define  MOD_CONF_MODULE_ENABLE_14       12      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_11         13      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_35           14
#define  MOD_CONF_MODULE_ENABLE_13       15      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_10         16      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_34           17
#define  MOD_CONF_MODULE_ENABLE_12       18      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_9          19      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_33           20
#define  MOD_CONF_MODULE_ENABLE_11       21      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_8          22      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_27           23
#define  MOD_CONF_MODULE_ENABLE_10       24      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_7          25      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CLOCK_MODULE_ENABLE    26      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ENABLE_9        27      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_26           28
#define  MOD_CONF_MODULE_ADDR_6          29      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_MODULE_ENABLE_8        30      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_25           31
#define  MOD_CONF_MODULE_ADDR_5          32      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_MODULE_ENABLE_7        33      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_24           34
#define  MOD_CONF_MODULE_ADDR_4          35      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_MODULE_ENABLE_6        36      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_23           37
#define  MOD_CONF_MODULE_ADDR_3          38      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_MODULE_ENABLE_5        39      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_22           40
#define  MOD_CONF_MODULE_ADDR_2          41      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_MODULE_ENABLE_4        42      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_2            43
#define  MOD_CONF_DECORATION_18          44
#define  MOD_CONF_DECORATION_17          45
#define  MOD_CONF_MODULE_ENABLE_3        46      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_MODULE_ADDR_1          47      /* callback function: CB_ModuleAddrConf */
#define  MOD_CONF_CURSORMSG_1            48
#define  MOD_CONF_MODULE_ENABLE_2        49      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_CURSORMSG_29           50
#define  MOD_CONF_CURSORMSG_30           51
#define  MOD_CONF_CURSORMSG_21           52
#define  MOD_CONF_CURSORMSG_20           53
#define  MOD_CONF_MODULE_ENABLE_1        54      /* callback function: CB_ModuleEnableConf */
#define  MOD_CONF_PICTURE                55

#define  OFFLI_CTRL                      8
#define  OFFLI_CTRL_GATE6_START_INDEX    2
#define  OFFLI_CTRL_GATE8_START_INDEX    3
#define  OFFLI_CTRL_GATE7_START_INDEX    4
#define  OFFLI_CTRL_GATE8_LENGTH         5
#define  OFFLI_CTRL_GATE5_START_INDEX    6
#define  OFFLI_CTRL_GATE7_LENGTH         7
#define  OFFLI_CTRL_GATE6_LENGTH         8
#define  OFFLI_CTRL_GATE5_LENGTH         9
#define  OFFLI_CTRL_GATE2_START_INDEX    10
#define  OFFLI_CTRL_GATE4_START_INDEX    11
#define  OFFLI_CTRL_GATE3_START_INDEX    12
#define  OFFLI_CTRL_GATE4_LENGTH         13
#define  OFFLI_CTRL_GATE1_START_INDEX    14
#define  OFFLI_CTRL_GATE3_LENGTH         15
#define  OFFLI_CTRL_GATE2_LENGTH         16
#define  OFFLI_CTRL_GATE1_LENGTH         17
#define  OFFLI_CTRL_SAMPLE_RAW_LENGTH    18
#define  OFFLI_CTRL_MAIN_GATE_PRETRIGGER 19
#define  OFFLI_CTRL_SAMPLE_RAW_STARTINDEX 20
#define  OFFLI_CTRL_MAIN_GATE_LENGTH     21
#define  OFFLI_CTRL_GATE_HEADER_LENGTH   22
#define  OFFLI_CTRL_RAW_DATA_SAMPLE_MODE 23
#define  OFFLI_CTRL_STRING_DATAFILE_NAME 24
#define  OFFLI_CTRL_FILE_CHANNEL_SIZE    25
#define  OFFLI_CTRL_FILE_READOUT_MODE    26
#define  OFFLI_CTRL_SIS9300_MODE_CLK     27
#define  OFFLI_CTRL_CURSORMSG_22         28
#define  OFFLI_CTRL_SIS3820_MODE_CLK     29
#define  OFFLI_CTRL_CHECKBOX_DISPL_RAW   30      /* callback function: CB_OfflineCheckBoxRun */
#define  OFFLI_CTRL_CHECKBOX_DISPL_ENSPEC 31     /* callback function: CB_OfflineCheckBoxRun */
#define  OFFLI_CTRL_CHECKBOX_DISPL_ENER_V 32     /* callback function: CB_OfflineCheckBoxRun */
#define  OFFLI_CTRL_FILE_EVENT_HEADER    33
#define  OFFLI_CTRL_FILE_EVENT_NOF_CHA   34
#define  OFFLI_CTRL_FILE_BUFFER_NUMBER   35
#define  OFFLI_CTRL_EVENT_NUMBER         36
#define  OFFLI_CTRL_DECORATION_7         37
#define  OFFLI_CTRL_DECORATION_6         38
#define  OFFLI_CTRL_FILE_NUMBER          39
#define  OFFLI_CTRL_GATE_EVENT_LEN       40
#define  OFFLI_CTRL_SIS_DEVICE           41
#define  OFFLI_CTRL_FILE_DATA_FORMAT     42
#define  OFFLI_CTRL_FILE_NOF_MODULES     43
#define  OFFLI_CTRL_SGL_STEP_NEXT        44      /* callback function: CB_Sgl_Step_Next */
#define  OFFLI_CTRL_CHECKBOX_STOP_IF_PILE 45     /* callback function: CB_OfflineCheckBoxRun */
#define  OFFLI_CTRL_CHECKBOX_SGL_STEP_EN 46      /* callback function: CB_OfflineCheckBoxRun */
#define  OFFLI_CTRL_STOP_LOOP            47      /* callback function: CB_Stop_Loop */
#define  OFFLI_CTRL_READ_FILE            48      /* callback function: CB_OfflineReadFileAndStart */

#define  PANEL                           9
#define  PANEL_STRING_CONFFILE_NAME      2
#define  PANEL_MODULE_TABLE_2            3
#define  PANEL_MODULE1_TABLE             4
#define  PANEL_DECORATION_18             5
#define  PANEL_SYSTEM_LED                6       /* callback function: CB_SystemStatusLed */
#define  PANEL_PICTURE_2                 7

#define  PANEL_DIAG                      10
#define  PANEL_DIAG_GRAPH_PATT3          2
#define  PANEL_DIAG_GRAPH_PATT1          3
#define  PANEL_DIAG_PRINT                4       /* callback function: CB_PrintPanelDiagnostic */
#define  PANEL_DIAG_CLOSE                5       /* callback function: CB_ClosePanelDisplayDiagnostic */
#define  PANEL_DIAG_RESET                6       /* callback function: CB_Diag_Pattern_Reset */
#define  PANEL_DIAG_GRAPH_PATT4          7
#define  PANEL_DIAG_GRAPH_PATT2          8

#define  PANEL_ESPE                      11
#define  PANEL_ESPE_RING_HISTO_CHOOSE    2       /* callback function: CB_DisplayEnergySpectrumChooseAdcShow */
#define  PANEL_ESPE_RING_ADC_CHOOSE      3       /* callback function: CB_DisplayEnergySpectrumChooseAdcShow */
#define  PANEL_ESPE_CLOSE                4       /* callback function: CB_ClosePanelDisplayEnergySpectrum */
#define  PANEL_ESPE_Y_ZOOM_IN            5       /* callback function: CB_DisplayEnergySpectrumZoomIn */
#define  PANEL_ESPE_X_ZOOM_IN            6       /* callback function: CB_DisplayEnergySpectrumZoomIn */
#define  PANEL_ESPE_MAX_PEAK_ZOOM_IN     7       /* callback function: CB_DisplayEnergySpectrumZoomPeak */
#define  PANEL_ESPE_XY_ZOOM_IN           8       /* callback function: CB_DisplayEnergySpectrumZoomIn */
#define  PANEL_ESPE_XY_EXPAND            9       /* callback function: CB_Expand_DisplayEnergySpectrum */
#define  PANEL_ESPE_Y_EXPAND             10      /* callback function: CB_Expand_DisplayEnergySpectrum */
#define  PANEL_ESPE_MODULE_NUMBER        11      /* callback function: CB_DisplayEnergySpectrumModuleNumber */
#define  PANEL_ESPE_X_EXPAND             12      /* callback function: CB_Expand_DisplayEnergySpectrum */
#define  PANEL_ESPE_CHECKBOX_LOG         13      /* callback function: CB_CheckDisplayEnergySpectrum */
#define  PANEL_ESPE_ENERGY_XMAX_SCALE    14      /* callback function: CB_SetEnergySpectrumXScale */
#define  PANEL_ESPE_CHECKBOX_ZOOM        15      /* callback function: CB_CheckDisplayEnergySpectrum */
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_8  16
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_7  17
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_6  18
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_5  19
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_4  20
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_3  21
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_2  22
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_1  23
#define  PANEL_ESPE_GRAPH_ENERGY_SPEC_0  24      /* callback function: CB_MoveCursor_DisplayEnergySpectrum */
#define  PANEL_ESPE_Y_POSITION           25
#define  PANEL_ESPE_X_POSITION           26
#define  PANEL_ESPE_PEAKMSE              27
#define  PANEL_ESPE_PEAKINT              28
#define  PANEL_ESPE_ENERGY_XMIN_SCALE    29      /* callback function: CB_SetEnergySpectrumXScale */
#define  PANEL_ESPE_PEAKWIDTH            30
#define  PANEL_ESPE_PEAKPOS              31
#define  PANEL_ESPE_CURSORMSG_21         32
#define  PANEL_ESPE_CLREAR_BUTTOM        33      /* callback function: CB_ClearSpectrumHistograms */
#define  PANEL_ESPE_GAUSFIT_BUTTOM       34      /* callback function: CB_EnergySpectrumGaussFit */

#define  PANEL_EVAL                      12
#define  PANEL_EVAL_RING_ADC_CHOOSE      2       /* callback function: CB_DisplayEnergyValueChooseAdcShow */
#define  PANEL_EVAL_CLOSE                3       /* callback function: CB_ClosePanelDisplayEnergyValue */
#define  PANEL_EVAL_Y_ZOOM_IN            4       /* callback function: CB_DisplayEnergyValueZoomIn */
#define  PANEL_EVAL_X_ZOOM_IN            5       /* callback function: CB_DisplayEnergyValueZoomIn */
#define  PANEL_EVAL_XY_ZOOM_IN           6       /* callback function: CB_DisplayEnergyValueZoomIn */
#define  PANEL_EVAL_XY_EXPAND            7       /* callback function: CB_Expand_DisplayEnergyValue */
#define  PANEL_EVAL_Y_EXPAND             8       /* callback function: CB_Expand_DisplayEnergyValue */
#define  PANEL_EVAL_MODULE_NUMBER        9       /* callback function: CB_DisplayEnergyValueModuleNumber */
#define  PANEL_EVAL_X_EXPAND             10      /* callback function: CB_Expand_DisplayEnergyValue */
#define  PANEL_EVAL_Y_POSITION           11
#define  PANEL_EVAL_X_POSITION           12
#define  PANEL_EVAL_CHECKBOX_ZOOM        13      /* callback function: CB_CheckDisplayEnergyValue */
#define  PANEL_EVAL_CHECKBOX_CVI_ZOOM    14      /* callback function: CB_CheckDisplayEnergyValue */
#define  PANEL_EVAL_CURSORMSG_21         15
#define  PANEL_EVAL_GRAPH_EVAL1          16      /* callback function: CB_MoveCursor_DisplayEnergyValue */
#define  PANEL_EVAL_TRAPEZ_ENERGY_MIN    17
#define  PANEL_EVAL_TRAPEZ_ENERGY_MAX    18
#define  PANEL_EVAL_TRAPEZ_YMAX_SCALE    19      /* callback function: CB_SetTrapezDisplayYScale */
#define  PANEL_EVAL_TRAPEZ_YMIN_SCALE    20      /* callback function: CB_SetTrapezDisplayYScale */

#define  PANEL_GAUS                      13
#define  PANEL_GAUS_PEAKWIDTH_8          2
#define  PANEL_GAUS_PEAKPOS_8            3
#define  PANEL_GAUS_PEAKWIDTH_7          4
#define  PANEL_GAUS_PEAKPOS_7            5
#define  PANEL_GAUS_PEAKWIDTH_6          6
#define  PANEL_GAUS_PEAKPOS_6            7
#define  PANEL_GAUS_PEAKWIDTH_5          8
#define  PANEL_GAUS_PEAKPOS_5            9
#define  PANEL_GAUS_PEAKWIDTH_4          10
#define  PANEL_GAUS_PEAKPOS_4            11
#define  PANEL_GAUS_PEAKWIDTH_3          12
#define  PANEL_GAUS_PEAKPOS_3            13
#define  PANEL_GAUS_PEAKWIDTH_2          14
#define  PANEL_GAUS_PEAKPOS_2            15
#define  PANEL_GAUS_PEAKWIDTH_1          16
#define  PANEL_GAUS_PEAKPOS_1            17
#define  PANEL_GAUS_CURSORMSG_24         18
#define  PANEL_GAUS_CURSORMSG_23         19
#define  PANEL_GAUS_CURSORMSG_31         20
#define  PANEL_GAUS_CURSORMSG_30         21
#define  PANEL_GAUS_CURSORMSG_29         22
#define  PANEL_GAUS_CURSORMSG_28         23
#define  PANEL_GAUS_CURSORMSG_27         24
#define  PANEL_GAUS_CURSORMSG_26         25
#define  PANEL_GAUS_CURSORMSG_25         26
#define  PANEL_GAUS_CURSORMSG_22         27

#define  PANEL_RAW                       14
#define  PANEL_RAW_RING_ADC_CHOOSE       2       /* callback function: CB_DisplayRawChooseAdcShow */
#define  PANEL_RAW_CLOSE                 3       /* callback function: CB_ClosePanelDisplayRaw */
#define  PANEL_RAW_PRINT                 4       /* callback function: CB_PrintPanelRaw */
#define  PANEL_RAW_Y_ZOOM_IN_RAW         5       /* callback function: CB_DisplayRawZoomIn */
#define  PANEL_RAW_T8_LED                6
#define  PANEL_RAW_T7_LED                7
#define  PANEL_RAW_T6_LED                8
#define  PANEL_RAW_T5_LED                9
#define  PANEL_RAW_T4_LED                10
#define  PANEL_RAW_T3_LED                11
#define  PANEL_RAW_T2_LED                12
#define  PANEL_RAW_T1_LED                13
#define  PANEL_RAW_X_ZOOM_IN_RAW         14      /* callback function: CB_DisplayRawZoomIn */
#define  PANEL_RAW_XY_ZOOM_IN_RAW        15      /* callback function: CB_DisplayRawZoomIn */
#define  PANEL_RAW_XY_EXPAND_RAW         16      /* callback function: CB_DisplayExpand_Raw */
#define  PANEL_RAW_Y_EXPAND_RAW          17      /* callback function: CB_DisplayExpand_Raw */
#define  PANEL_RAW_MODULE_NUMBER         18      /* callback function: CB_DisplayRawModuleNumber */
#define  PANEL_RAW_X_EXPAND_RAW          19      /* callback function: CB_DisplayExpand_Raw */
#define  PANEL_RAW_Y_POSITION            20
#define  PANEL_RAW_X_POSITION            21
#define  PANEL_RAW_CHECKBOX_ZOOM         22      /* callback function: CB_CheckDisplayRaw */
#define  PANEL_RAW_CHECKBOX_DELETE_DISAB 23      /* callback function: CB_CheckDisplayRaw */
#define  PANEL_RAW_CHECKBOX_CVI_ZOOM     24      /* callback function: CB_CheckDisplayRaw */
#define  PANEL_RAW_CURSORMSG_21          25
#define  PANEL_RAW_TIMESTAMP_LOWER       26
#define  PANEL_RAW_PILEUP_INFO           27
#define  PANEL_RAW_TRAILER               28
#define  PANEL_RAW_ACCU_GATE8            29
#define  PANEL_RAW_ACCU_GATE7            30
#define  PANEL_RAW_ACCU_GATE6            31
#define  PANEL_RAW_ACCU_GATE5            32
#define  PANEL_RAW_ACCU_GATE4            33
#define  PANEL_RAW_ACCU_GATE3            34
#define  PANEL_RAW_ACCU_GATE2            35
#define  PANEL_RAW_ACCU_GATE1            36
#define  PANEL_RAW_PEAKHIGH_INDEX        37
#define  PANEL_RAW_PEAKHIGH_VALUE        38
#define  PANEL_RAW_HEADER_ID             39
#define  PANEL_RAW_TIMESTAMP_UPPER       40
#define  PANEL_RAW_DECORATION_7          41
#define  PANEL_RAW_GRAPH_RAW             42      /* callback function: CB_MoveCursor_DisplayRaw */

#define  RUN_CTRL                        15
#define  RUN_CTRL_STOPBUTTOM             2       /* callback function: CB_RunStopAcq */
#define  RUN_CTRL_STARTBUTTOM            3       /* callback function: CB_RunStartAcq */
#define  RUN_CTRL_DATA_FILE_SIZE         4
#define  RUN_CTRL_STRING_USBTS_FILE_NAM  5
#define  RUN_CTRL_STRING_DATAFILE_NAME   6
#define  RUN_CTRL_DATA_FILE_VNR          7
#define  RUN_CTRL_RUN_EVENT_MAX_SECOND   8       /* callback function: CB_RunEventMaxSeconds */
#define  RUN_CTRL_RUN_EVENT_MAX_NUMBER2  9
#define  RUN_CTRL_NOF_EVENT_READ         10
#define  RUN_CTRL_RUN_EVENT_MAX_NUMBER   11      /* callback function: CB_RunEventMaxNumber */
#define  RUN_CTRL_RUN_EVENT_MBYTE        12
#define  RUN_CTRL_RUN_EVENT_SECOND       13
#define  RUN_CTRL_RUN_EVENT_RATE_A       14
#define  RUN_CTRL_LED_LOOP               15
#define  RUN_CTRL_RUN_EVENT_RATE         16
#define  RUN_CTRL_RUN_EVENT_NUMBER       17
#define  RUN_CTRL_READOUT_MODE           18      /* callback function: CB_Run_ReadoutMode */
#define  RUN_CTRL_CURSORMSG_23           19
#define  RUN_CTRL_CURSORMSG_22           20
#define  RUN_CTRL_DECORATION_7           21
#define  RUN_CTRL_DECORATION_6           22
#define  RUN_CTRL_CHECKBOX_WR_DATA       23      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_START_CLR_DI  24      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_DISPL_RAW     25      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_DISPL_ENER_V  26      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_DISPL_DIAG    27      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_DISPL_ENSPEC  28      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_STOP_EVENT    29      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECK_NOF_EVENT_MANUA  30      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_CHECKBOX_STOP_TIME     31      /* callback function: CB_CheckBoxRun */
#define  RUN_CTRL_ONE_M_SECOND_TICK      32      /* callback function: CB_Run10mSecondTick */
#define  RUN_CTRL_ONE_SECOND_TICK        33      /* callback function: CB_RunSecondTick */
#define  RUN_CTRL_DECORATION             34

#define  SAMPL_CONF                      16
#define  SAMPL_CONF_GATE6_START_INDEX    2       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE8_START_INDEX    3       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE7_START_INDEX    4       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE8_LENGTH         5       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE5_START_INDEX    6       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE7_LENGTH         7       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE6_LENGTH         8       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE5_LENGTH         9       /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE2_START_INDEX    10      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE4_START_INDEX    11      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE3_START_INDEX    12      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE4_LENGTH         13      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE1_START_INDEX    14      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE3_LENGTH         15      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE2_LENGTH         16      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_GATE1_LENGTH         17      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_SAMPLE_RAW_LENGTH    18      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_MAIN_GATE_PRETRIGGER 19      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_MAIN_GATE_LENGTH     20      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_SAMPLE_RAW_STARTINDEX 21     /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_CURSORMSG_54         22
#define  SAMPL_CONF_CURSORMSG_34         23
#define  SAMPL_CONF_DECORATION_19        24
#define  SAMPL_CONF_RAW_DATA_TEST_FIR    25      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_ACCU_DATA_FORMAT     26      /* callback function: CB_SampleModeConf */
#define  SAMPL_CONF_RAW_DATA_SAMPLE_MODE 27      /* callback function: CB_SampleModeConf */

#define  SIGNA_CONF                      17
#define  SIGNA_CONF_CURSORMSG_14         2
#define  SIGNA_CONF_CURSORMSG_15         3
#define  SIGNA_CONF_CURSORMSG_16         4
#define  SIGNA_CONF_CURSORMSG_17         5
#define  SIGNA_CONF_CURSORMSG_9          6
#define  SIGNA_CONF_CURSORMSG_8          7
#define  SIGNA_CONF_CURSORMSG_7          8
#define  SIGNA_CONF_CURSORMSG_41         9
#define  SIGNA_CONF_CURSORMSG_38         10
#define  SIGNA_CONF_DECORATION_17        11
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC8 12     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC7 13     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC6 14     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC5 15     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC4 16     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC3 17     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC2 18     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_CHECK_INVERTPULS_ADC1 19     /* callback function: CB_ADC_InvertFlags */
#define  SIGNA_CONF_INVERT_TABLE         20

#define  T1_DIAGFFT                      18
#define  T1_DIAGFFT_CLOSE                2       /* callback function: CB_ClosePanelTest1FFT */
#define  T1_DIAGFFT_RING_MODE_3          3       /* callback function: CB_ChooseFftShow */
#define  T1_DIAGFFT_WINDOW               4
#define  T1_DIAGFFT_SCALING              5
#define  T1_DIAGFFT_PEAK_FREQ_4          6
#define  T1_DIAGFFT_PEAK_FREQ_3          7
#define  T1_DIAGFFT_PEAK_FREQ_2          8
#define  T1_DIAGFFT_PEAK_FREQ            9
#define  T1_DIAGFFT_FFT_XMAX_SCALE       10      /* callback function: CB_SetFftXYScale */
#define  T1_DIAGFFT_DISPLAY              11
#define  T1_DIAGFFT_FFT_XMIN_SCALE       12      /* callback function: CB_SetFftXYScale */
#define  T1_DIAGFFT_POWER_PEAK           13
#define  T1_DIAGFFT_FFT_YMAX_SCALE       14      /* callback function: CB_SetFftXYScale */
#define  T1_DIAGFFT_DBGRAPH              15
#define  T1_DIAGFFT_FFTGRAPH             16
#define  T1_DIAGFFT_FFT_YMIN_SCALE       17      /* callback function: CB_SetFftXYScale */
#define  T1_DIAGFFT_TEXTMSG_7            18
#define  T1_DIAGFFT_TEXTMSG_6            19
#define  T1_DIAGFFT_TEXTMSG_4            20
#define  T1_DIAGFFT_UNIT                 21
#define  T1_DIAGFFT_UNIT_2               22

#define  T1_DIAGHIS                      19
#define  T1_DIAGHIS_CLOSE                2       /* callback function: CB_ClosePanelTest1Histo */
#define  T1_DIAGHIS_RING_MODE_3          3       /* callback function: CB_ChooseHistoShow */
#define  T1_DIAGHIS_HISTOGRAPH           4
#define  T1_DIAGHIS_HISTO_XMAX_SCALE     5       /* callback function: CB_SetHistoXYScale */
#define  T1_DIAGHIS_HISTO_XMIN_SCALE     6       /* callback function: CB_SetHistoXYScale */
#define  T1_DIAGHIS_HISTO_YMAX_SCALE     7       /* callback function: CB_SetHistoXYScale */
#define  T1_DIAGHIS_HISTO_YMIN_SCALE     8       /* callback function: CB_SetHistoXYScale */
#define  T1_DIAGHIS_STD_DEV_ADC1         9
#define  T1_DIAGHIS_STD_DEV_ADC2         10
#define  T1_DIAGHIS_STD_DEV_ADC3         11
#define  T1_DIAGHIS_MEAN_ADC1            12
#define  T1_DIAGHIS_STD_DEV_ADC4         13
#define  T1_DIAGHIS_MEAN_ADC2            14
#define  T1_DIAGHIS_STD_DEV_ADC5         15
#define  T1_DIAGHIS_MEAN_ADC3            16
#define  T1_DIAGHIS_STD_DEV_ADC6         17
#define  T1_DIAGHIS_MEAN_ADC4            18
#define  T1_DIAGHIS_STD_DEV_ADC7         19
#define  T1_DIAGHIS_MEAN_ADC5            20
#define  T1_DIAGHIS_STD_DEV_ADC8         21
#define  T1_DIAGHIS_MEAN_ADC6            22
#define  T1_DIAGHIS_MEAN_ADC7            23
#define  T1_DIAGHIS_MEAN_ADC8            24
#define  T1_DIAGHIS_MEAN                 25
#define  T1_DIAGHIS_MEAN_2               26
#define  T1_DIAGHIS_StdDev               27

#define  T1_DIAGLON                      20
#define  T1_DIAGLON_READ_DATA            2       /* callback function: CB_Offline_Read_DataEvent */
#define  T1_DIAGLON_CLOSE                3       /* callback function: CB_ClosePanelTest1LongTerm */
#define  T1_DIAGLON_OFFLINE_TIME         4       /* callback function: CB_OfflineLoopTime */
#define  T1_DIAGLON_OFFLINE_TICK         5       /* callback function: CB_Offline_Timer */
#define  T1_DIAGLON_OFFLINE_RUN_PLAYBACK 6       /* callback function: CB_OfflineStartStopRUN_Playback */
#define  T1_DIAGLON_GET_EVENT_NUMBER     7       /* callback function: CB_Offline_Read_DataEvent */

#define  TEST1_MENU                      21
#define  TEST1_MENU_STOPBUTTOM           2       /* callback function: CB_StopAcq */
#define  TEST1_MENU_STARTBUTTOM          3       /* callback function: CB_StartAcq */
#define  TEST1_MENU_CLOSE                4       /* callback function: CB_ClosePanelAdcTest1Menue */
#define  TEST1_MENU_CHECKBOX_DISPL_LONG_T 5      /* callback function: CB_CheckBoxTest1 */
#define  TEST1_MENU_CHECKBOX_DISPL_FFT   6       /* callback function: CB_CheckBoxTest1 */
#define  TEST1_MENU_CHECKBOX_DISPL_HISTO 7       /* callback function: CB_CheckBoxTest1 */
#define  TEST1_MENU_CHECKBOX_DISPL_RAW   8       /* callback function: CB_CheckBoxTest1 */
#define  TEST1_MENU_RING_MODE_CLK        9       /* callback function: CB_ClockMode */
#define  TEST1_MENU_TRIGGER_ADC          10      /* callback function: CB_Trigger_ADC */
#define  TEST1_MENU_RUN_EVENT_SECOND     11
#define  TEST1_MENU_ONE_SECOND_TICK      12      /* callback function: CB_RunSecondTick */
#define  TEST1_MENU_ADC_OFFSET_1         13      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_2         14      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_3         15      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_4         16      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_5         17      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_6         18      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_7         19      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_OFFSET_8         20      /* callback function: CB_ADC_Offset */
#define  TEST1_MENU_ADC_GAIN_8           21      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_7           22      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_6           23      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_CURSORMSG_8          24
#define  TEST1_MENU_CURSORMSG_7          25
#define  TEST1_MENU_CURSORMSG_6          26
#define  TEST1_MENU_CURSORMSG_5          27
#define  TEST1_MENU_CURSORMSG_4          28
#define  TEST1_MENU_CURSORMSG_3          29
#define  TEST1_MENU_CURSORMSG_2          30
#define  TEST1_MENU_CURSORMSG_1          31
#define  TEST1_MENU_ADC_GAIN_5           32      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_4           33      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_3           34      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_2           35      /* callback function: CB_ADC_Gain */
#define  TEST1_MENU_ADC_GAIN_1           36      /* callback function: CB_ADC_Gain */

#define  TRIG_CONF                       22
#define  TRIG_CONF_ADC_COUNTS_5          2
#define  TRIG_CONF_ADC_COUNTS_6          3
#define  TRIG_CONF_ADC_COUNTS_8          4
#define  TRIG_CONF_ADC_COUNTS_7          5
#define  TRIG_CONF_RING_MODE_TRIGGER_8   6       /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_7   7       /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_6   8       /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_5   9       /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_4   10      /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_3   11      /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_2   12      /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_RING_MODE_TRIGGER_1   13      /* callback function: CB_TriggerCondition */
#define  TRIG_CONF_ADC_COUNTS_1          14
#define  TRIG_CONF_ADC_COUNTS_2          15
#define  TRIG_CONF_ADC_COUNTS_3          16
#define  TRIG_CONF_ADC_COUNTS_4          17
#define  TRIG_CONF_DECORATION_18         18
#define  TRIG_CONF_DECORATION_17         19
#define  TRIG_CONF_CURSORMSG_6           20
#define  TRIG_CONF_CURSORMSG_14          21
#define  TRIG_CONF_CURSORMSG_15          22
#define  TRIG_CONF_CURSORMSG_16          23
#define  TRIG_CONF_CURSORMSG_17          24
#define  TRIG_CONF_CURSORMSG_9           25
#define  TRIG_CONF_CURSORMSG_8           26
#define  TRIG_CONF_CURSORMSG_7           27
#define  TRIG_CONF_FIR_TRIGGER_THRES_5   28      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_CURSORMSG_35          29
#define  TRIG_CONF_CURSORMSG_34          30
#define  TRIG_CONF_CURSORMSG_33          31
#define  TRIG_CONF_FIR_TRIGGER_THRES_6   32      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_THRES_7   33      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_THRES_8   34      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_G_7       35      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_6       36      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_5       37      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_8       38      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_5 39      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_6 40      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_TRIG_TABLE_PLENGTH    41
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_7 42      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_8 43      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_P_5       44      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_FIR_TRIGGER_P_6       45      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_FIR_TRIGGER_P_7       46      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_FIR_TRIGGER_P_8       47      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_CURSORMSG_5           48
#define  TRIG_CONF_FIR_TRIGGER_THRES_1   49      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_THRES_2   50      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_THRES_3   51      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_THRES_4   52      /* callback function: CB_ADC_FirTriggerThreshold */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_1 53      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_2 54      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_TRIG_TABLE_PG         55
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_3 56      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_PLENGTH_4 57      /* callback function: CB_ADC_FirTriggerPulsLength */
#define  TRIG_CONF_FIR_TRIGGER_G_3       58      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_2       59      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_1       60      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_G_4       61      /* callback function: CB_ADC_FirTriggerG */
#define  TRIG_CONF_FIR_TRIGGER_P_1       62      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_FIR_TRIGGER_P_2       63      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_TRIG_OUT              64
#define  TRIG_CONF_TRIG_TABLE            65
#define  TRIG_CONF_FIR_TRIGGER_P_3       66      /* callback function: CB_ADC_FirTriggerP */
#define  TRIG_CONF_FIR_TRIGGER_P_4       67      /* callback function: CB_ADC_FirTriggerP */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENU                            1
#define  MENU_FILE                       2
#define  MENU_FILE_QUIT                  3       /* callback function: CB_MenuFile */
#define  MENU_VIEW                       4
#define  MENU_VIEW_MESSAGES              5
#define  MENU_VIEW_MESSAGES_SUBMENU      6
#define  MENU_VIEW_MESSAGES_SYSTEM       7       /* callback function: CB_MenuMessages */
#define  MENU_VIEW_MESSAGES_ERROR        8       /* callback function: CB_MenuMessages */
#define  MENU_CONFIGURATION              9
#define  MENU_CONFIGURATION_CONFIGUR     10      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SEPARATOR    11
#define  MENU_CONFIGURATION_LOAD         12      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SEPARATOR_3  13
#define  MENU_CONFIGURATION_SAVE         14      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SAVEAS       15      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SEPARATOR_2  16
#define  MENU_CONFIGURATION_MODULES      17      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_CLOCK_PARAM  18      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_DAC_PARAM    19      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_TRIGGER_PARAM 20     /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SAMPLE_PARAM 21      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SIGNAL_INVERT 22     /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_GAIN_FACTOR  23      /* callback function: CB_MenuConf */
#define  MENU_CONFIGURATION_SEPARATOR_4  24
#define  MENU_RUN_MENUE                  25
#define  MENU_RUN_MENUE_OPENPANEL        26      /* callback function: CB_OpenPanelRunControl */
#define  MENU_RUN_MENUE_SEPARATOR_5      27
#define  MENU_OFFLINE_DIAG               28
#define  MENU_OFFLINE_DIAG_OPENPANEL     29      /* callback function: CB_OpenPanelOfflineControl */
#define  MENU_OFFLINE_DIAG_SEPARATOR_6   30
#define  MENU_TEST_MENUS                 31
#define  MENU_TEST_MENUS_OPENPANEL_TEST1 32
#define  MENU_TEST_MENUS_OPENPANEL_TEST2 33
#define  MENU_TEST_MENUS_SEPARATOR_7     34

#define  MENUBAR                         2

#define  MENUCONEN                       3
#define  MENUCONEN_PANEL                 2
#define  MENUCONEN_PANEL_CLOSE           3       /* callback function: CB_Menu_DecayTimeConfiguration */

#define  MENUCONFCK                      4
#define  MENUCONFCK_PANEL                2
#define  MENUCONFCK_PANEL_CLOSE          3       /* callback function: CB_Menu_ClockParameterConfiguration */

#define  MENUCONFDA                      5
#define  MENUCONFDA_PANEL                2
#define  MENUCONFDA_PANEL_CLOSE          3       /* callback function: CB_Menu_DacOffset_Configuration */
#define  MENUCONFDA_PANEL_SEPARATOR      4
#define  MENUCONFDA_GET                  5
#define  MENUCONFDA_GET_MODULE1          6       /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE2          7       /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE3          8       /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE4          9       /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE5          10      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE6          11      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE7          12      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE8          13      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE9          14      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE10         15      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE11         16      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE12         17      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE13         18      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_MODULE14         19      /* callback function: CB_GetDacOffsetToTable */
#define  MENUCONFDA_GET_SEPARATOR_2      20
#define  MENUCONFDA_PUT                  21
#define  MENUCONFDA_PUT_MODULE1          22      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE2          23      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE3          24      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE4          25      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE5          26      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE6          27      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE7          28      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE8          29      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE9          30      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE10         31      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE11         32      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE12         33      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE13         34      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_MODULE14         35      /* callback function: CB_PutDacOffsetToTable */
#define  MENUCONFDA_PUT_SEPARATOR_3      36
#define  MENUCONFDA_CONFIG               37
#define  MENUCONFDA_CONFIG_ALL_DACS      38      /* callback function: CB_Menu_DacOffset_Configuration */
#define  MENUCONFDA_CONFIG_SEPARATOR_4   39
#define  MENUCONFDA_READ                 40
#define  MENUCONFDA_READ_LOOP_ON         41      /* callback function: CB_Menu_DacOffset_Configuration */
#define  MENUCONFDA_READ_LOOP_OFF        42      /* callback function: CB_Menu_DacOffset_Configuration */
#define  MENUCONFDA_READ_SEPARATOR_5     43

#define  MENUCONFGF                      6
#define  MENUCONFGF_PANEL                2
#define  MENUCONFGF_PANEL_CLOSE          3       /* callback function: CB_Menu_Gain_Factor_Configuration */
#define  MENUCONFGF_PANEL_SEPARATOR      4
#define  MENUCONFGF_GET                  5
#define  MENUCONFGF_GET_MODULE1          6       /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE2          7       /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE3          8       /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE4          9       /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE5          10      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE6          11      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE7          12      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE8          13      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE9          14      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE10         15      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE11         16      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE12         17      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE13         18      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_MODULE14         19      /* callback function: CB_GetGain_FactorFlagToTable */
#define  MENUCONFGF_GET_SEPARATOR_2      20
#define  MENUCONFGF_PUT                  21
#define  MENUCONFGF_PUT_MODULE1          22      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE2          23      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE3          24      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE4          25      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE5          26      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE6          27      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE7          28      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE8          29      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE9          30      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE10         31      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE11         32      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE12         33      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE13         34      /* callback function: CB_PutGain_FactorFlagToTable */
#define  MENUCONFGF_PUT_MODULE14         35      /* callback function: CB_PutGain_FactorFlagToTable */

#define  MENUCONFMO                      7
#define  MENUCONFMO_PANEL                2
#define  MENUCONFMO_PANEL_CLOSE          3       /* callback function: CB_Menu_ModuleConfiguration */
#define  MENUCONFMO_TESTS                4
#define  MENUCONFMO_TESTS_LEDTEST        5       /* callback function: CB_Menu_ModuleLedTest */

#define  MENUCONFSA                      8
#define  MENUCONFSA_PANEL                2
#define  MENUCONFSA_PANEL_CLOSE          3       /* callback function: CB_Menu_CommonParameterConfiguration */
#define  MENUCONFSA_DEF_TS_LOADER        4       /* callback function: CB_Menu_CommonParameterConfiguration */
#define  MENUCONFSA_HELP                 5
#define  MENUCONFSA_HELP_SHOW_GATE_DIAGR 6       /* callback function: CB_Menu_CommonParameterConfiguration */

#define  MENUCONFSI                      9
#define  MENUCONFSI_PANEL                2
#define  MENUCONFSI_PANEL_CLOSE          3       /* callback function: CB_Menu_Signal_Invert_Configuration */
#define  MENUCONFSI_PANEL_SEPARATOR      4
#define  MENUCONFSI_GET                  5
#define  MENUCONFSI_GET_MODULE1          6       /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE2          7       /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE3          8       /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE4          9       /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE5          10      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE6          11      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE7          12      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE8          13      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE9          14      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE10         15      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE11         16      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE12         17      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE13         18      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_MODULE14         19      /* callback function: CB_GetADCSignal_InvertFlagToTable */
#define  MENUCONFSI_GET_SEPARATOR_2      20
#define  MENUCONFSI_PUT                  21
#define  MENUCONFSI_PUT_MODULE1          22      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE2          23      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE3          24      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE4          25      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE5          26      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE6          27      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE7          28      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE8          29      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE9          30      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE10         31      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE11         32      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE12         33      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE13         34      /* callback function: CB_PutADCSignal_InvertFlagToTable */
#define  MENUCONFSI_PUT_MODULE14         35      /* callback function: CB_PutADCSignal_InvertFlagToTable */

#define  MENUCONFTR                      10
#define  MENUCONFTR_PANEL                2
#define  MENUCONFTR_PANEL_CLOSE          3       /* callback function: CB_Menu_TriggerConfiguration */
#define  MENUCONFTR_PANEL_SEPARATOR      4
#define  MENUCONFTR_GET                  5
#define  MENUCONFTR_GET_MODULE1          6       /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE2          7       /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE3          8       /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE4          9       /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE5          10      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE6          11      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE7          12      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE8          13      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE9          14      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE10         15      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE11         16      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE12         17      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE13         18      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_MODULE14         19      /* callback function: CB_GetTrigValueToTable */
#define  MENUCONFTR_GET_SEPARATOR_2      20
#define  MENUCONFTR_PUT                  21
#define  MENUCONFTR_PUT_MODULE1          22      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE2          23      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE3          24      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE4          25      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE5          26      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE6          27      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE7          28      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE8          29      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE9          30      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE10         31      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE11         32      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE12         33      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE13         34      /* callback function: CB_PutTrigValueToTable */
#define  MENUCONFTR_PUT_MODULE14         35      /* callback function: CB_PutTrigValueToTable */

#define  MENUCONFyy                      11
#define  MENUCONFyy_PANEL                2
#define  MENUCONFyy_PANEL_CLOSE          3       /* callback function: CB_Menu_DecayTimeConfiguration */

#define  MENUCTRLOF                      12
#define  MENUCTRLOF_PANEL                2
#define  MENUCTRLOF_PANEL_CLOSE          3       /* callback function: CB_MenuOfflineControl */
#define  MENUCTRLOF_FILE                 4
#define  MENUCTRLOF_FILE_DEFINE_FILENAME 5       /* callback function: CB_MenuOfflineControl */

#define  MENUCTRLRU                      13
#define  MENUCTRLRU_PANEL                2
#define  MENUCTRLRU_PANEL_CLOSE          3       /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_FILE                 4
#define  MENUCTRLRU_FILE_CHANGE_DATA_FILE 5      /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_FILE_CHANGE_USBTSFILE 6      /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_WINDOW               7
#define  MENUCTRLRU_WINDOW_RUN_RAW_ACTIV 8       /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_WINDOW_RUN_FPGA_ACTIV 9      /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_WINDOW_RUN_SPEC_ACTIV 10     /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_WINDOW_RUN_DIAG_ACTIV 11     /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_TEST_TRIGGER         12
#define  MENUCTRLRU_TEST_TRIGGER_LOOP_ON 13      /* callback function: CB_MenuRunControl */
#define  MENUCTRLRU_TEST_TRIGGER_LOOP_OFF 14     /* callback function: CB_MenuRunControl */

#define  MENUDIAG                        14
#define  MENUDIAG_PANEL                  2
#define  MENUDIAG_PANEL_CLOSE            3       /* callback function: CB_MenuDiagnostic */

#define  MENUDIAG_2                      15
#define  MENUDIAG_2_PANEL                2
#define  MENUDIAG_2_PANEL_CLOSE          3       /* callback function: CB_MenuDiagnostic */

#define  MENUDIAGRA                      16
#define  MENUDIAGRA_PANEL                2
#define  MENUDIAGRA_PANEL_CLOSE          3       /* callback function: CB_MenuDiagnosticRaw */

#define  MENUDIAGxx                      17
#define  MENUDIAGxx_PANEL                2
#define  MENUDIAGxx_PANEL_CLOSE          3       /* callback function: CB_MenuDiagnosticEnergy */

#define  MENUGR_ENE                      18
#define  MENUGR_ENE_PANEL                2
#define  MENUGR_ENE_PANEL_CLOSE          3       /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_PLOT_STYLE           4
#define  MENUGR_ENE_PLOT_STYLE_THIN_LINE 5       /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_PLOT_STYLE_FAT_LINE  6       /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_PLOT_STYLE_THIN_STEP 7       /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_PLOT_STYLE_FAT_STEP  8       /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_PLOT_STYLE_CON_POINTS 9      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_LINE_STYLE           10
#define  MENUGR_ENE_LINE_STYLE_SOLID     11      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_LINE_STYLE_DASH      12      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_LINE_STYLE_DOT       13      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_LINE_STYLE_DASH_DOT  14      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_LINE_STYLE_DASH_2XDOT 15     /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR         16
#define  MENUGR_ENE_BACKGR_COLOR_WHITE   17      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_OFFWHITE 18     /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_LT_GRAY 19      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_GRAY    20      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_DK_GRAY 21      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_TRANSP  22      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_BACKGR_COLOR_BLACK   23      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR           24
#define  MENUGR_ENE_GRID_COLOR_BLACK     25      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_TRANSP    26      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_DK_GRAY   27      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_GRAY      28      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_LT_GRAY   29      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_OFFWHITE  30      /* callback function: CB_MenuGraphEnergyValue */
#define  MENUGR_ENE_GRID_COLOR_WHITE     31      /* callback function: CB_MenuGraphEnergyValue */

#define  MENUGR_RAW                      19
#define  MENUGR_RAW_PANEL                2
#define  MENUGR_RAW_PANEL_CLOSE          3       /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_PLOT_STYLE           4
#define  MENUGR_RAW_PLOT_STYLE_THIN_LINE 5       /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_PLOT_STYLE_FAT_LINE  6       /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_PLOT_STYLE_THIN_STEP 7       /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_PLOT_STYLE_FAT_STEP  8       /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_PLOT_STYLE_CON_POINTS 9      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_LINE_STYLE           10
#define  MENUGR_RAW_LINE_STYLE_SOLID     11      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_LINE_STYLE_DASH      12      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_LINE_STYLE_DOT       13      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_LINE_STYLE_DASH_DOT  14      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_LINE_STYLE_DASH_2XDOT 15     /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR         16
#define  MENUGR_RAW_BACKGR_COLOR_WHITE   17      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_OFFWHITE 18     /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_LT_GRAY 19      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_GRAY    20      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_DK_GRAY 21      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_TRANSP  22      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_BACKGR_COLOR_BLACK   23      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR           24
#define  MENUGR_RAW_GRID_COLOR_BLACK     25      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_TRANSP    26      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_DK_GRAY   27      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_GRAY      28      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_LT_GRAY   29      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_OFFWHITE  30      /* callback function: CB_MenuGraphRaw */
#define  MENUGR_RAW_GRID_COLOR_WHITE     31      /* callback function: CB_MenuGraphRaw */

#define  MENUGR_SPE                      20
#define  MENUGR_SPE_PANEL                2
#define  MENUGR_SPE_PANEL_CLOSE          3       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR           4
#define  MENUGR_SPE_PLOT_COLOR_RED       5       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR_DK_RED    6       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR_GREEN     7       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR_YELLOW    8       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR_BLACK     9       /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_COLOR_WHITE     10      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE           11
#define  MENUGR_SPE_PLOT_STYLE_THIN_LINE 12      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_FAT_LINE  13      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_THIN_STEP 14      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_FAT_STEP  15      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_CON_POINTS 16     /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_VERTIC_BAR 17     /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_PLOT_STYLE_BVERTI_BAR 18     /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_LINE_STYLE           19
#define  MENUGR_SPE_LINE_STYLE_SOLID     20      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_LINE_STYLE_DASH      21      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_LINE_STYLE_DOT       22      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_LINE_STYLE_DASH_DOT  23      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_LINE_STYLE_DASH_2XDOT 24     /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR         25
#define  MENUGR_SPE_BACKGR_COLOR_WHITE   26      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_OFFWHITE 27     /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_LT_GRAY 28      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_GRAY    29      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_DK_GRAY 30      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_TRANSP  31      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_BACKGR_COLOR_BLACK   32      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR           33
#define  MENUGR_SPE_GRID_COLOR_BLACK     34      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_TRANSP    35      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_DK_GRAY   36      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_GRAY      37      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_LT_GRAY   38      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_OFFWHITE  39      /* callback function: CB_MenuGraphEnergySpec */
#define  MENUGR_SPE_GRID_COLOR_WHITE     40      /* callback function: CB_MenuGraphEnergySpec */

#define  MENUMESERR                      21
#define  MENUMESERR_CLOSE                2       /* callback function: CB_Menu_MessagesError */
#define  MENUMESERR_CLEAR                3       /* callback function: CB_Menu_MessagesError */

#define  MENUMESSYS                      22
#define  MENUMESSYS_CLOSE                2       /* callback function: CB_Menu_MessagesSystem */
#define  MENUMESSYS_CLEAR                3       /* callback function: CB_Menu_MessagesSystem */
#define  MENUMESSYS_TEST1                4       /* callback function: CB_Menu_MessagesSystem */

#define  MENUTEMP                        23
#define  MENUTEMP_FILE                   2
#define  MENUTEMP_FILE_QUIT              3       /* callback function: CB_MenuFile */

#define  Panel                           24


     /* Callback Prototypes: */ 

int  CVICALLBACK CB_ADC_FirTriggerG(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_FirTriggerP(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_FirTriggerPulsLength(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_FirTriggerThreshold(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_Gain(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_InvertFlags(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ADC_Offset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_CheckBoxRun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_CheckBoxTest1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_CheckDisplayEnergySpectrum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_CheckDisplayEnergyValue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_CheckDisplayRaw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ChooseFftShow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ChooseHistoShow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClearSpectrumHistograms(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClockConfFlags(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClockMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClockModeConf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelAdcTest1Menue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelDisplayDiagnostic(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelDisplayEnergySpectrum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelDisplayEnergyValue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelDisplayRaw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelTest1FFT(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelTest1Histo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ClosePanelTest1LongTerm(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DacOffsetConf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Diag_Pattern_Reset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergySpectrumChooseAdcShow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergySpectrumModuleNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergySpectrumZoomIn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergySpectrumZoomPeak(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergyValueChooseAdcShow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergyValueModuleNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayEnergyValueZoomIn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayExpand_Raw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayRawChooseAdcShow(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayRawModuleNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_DisplayRawZoomIn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_EnergySpectrumGaussFit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Expand_DisplayEnergySpectrum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Expand_DisplayEnergyValue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Gain_Flags(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK CB_GetADCSignal_InvertFlagToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_GetDacOffsetToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_GetGain_FactorFlagToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_GetTrigValueToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_ClockParameterConfiguration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_CommonParameterConfiguration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_DacOffset_Configuration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_DecayTimeConfiguration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_Gain_Factor_Configuration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_MessagesError(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_MessagesSystem(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_ModuleConfiguration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_ModuleLedTest(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_Signal_Invert_Configuration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_Menu_TriggerConfiguration(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuConf(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuDiagnostic(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuDiagnosticEnergy(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuDiagnosticRaw(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuFile(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuGraphEnergySpec(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuGraphEnergyValue(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuGraphRaw(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuMessages(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuOfflineControl(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_MenuRunControl(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK CB_ModuleAddrConf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_ModuleEnableConf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_MoveCursor_DisplayEnergySpectrum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_MoveCursor_DisplayEnergyValue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_MoveCursor_DisplayRaw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Offline_Read_DataEvent(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Offline_Timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_OfflineCheckBoxRun(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_OfflineLoopTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_OfflineReadFileAndStart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_OfflineStartStopRUN_Playback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK CB_OpenPanelOfflineControl(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_OpenPanelRunControl(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK CB_PrintPanelDiagnostic(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_PrintPanelRaw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK CB_PutADCSignal_InvertFlagToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_PutDacOffsetToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_PutGain_FactorFlagToTable(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK CB_PutTrigValueToTable(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK CB_Run10mSecondTick(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Run_ReadoutMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_RunEventMaxNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_RunEventMaxSeconds(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_RunSecondTick(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_RunStartAcq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_RunStopAcq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SampleModeConf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SetEnergySpectrumXScale(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SetFftXYScale(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SetHistoXYScale(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SetTrapezDisplayYScale(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Sgl_Step_Next(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SIS3320_ExternalConfFlags(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SIS3320_TriggerMode_Souce_Conf(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_StartAcq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Stop_Loop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_StopAcq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_SystemStatusLed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_Trigger_ADC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_TriggerCondition(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
