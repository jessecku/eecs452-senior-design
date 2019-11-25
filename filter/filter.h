
#define size  201
Int16 B1[201] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, -1, -1, -1, -1, -1,
		0, 1, 2, 3, 3, 2, 0, -2, -5, -7,
		-7, -5, -2, 3, 9, 13, 14, 11, 4, -5,
		-15, -22, -25, -21, -10, 6, 23, 37, 42, 37,
		20, -6, -34, -57, -69, -62, -37, 2, 47, 86,
		107, 101, 66, 7, -63, -125, -162, -158, -111, -25,
		79, 177, 240, 244, 182, 60, -96, -248, -354, -377,
		-299, -125, 111, 354, 539, 605, 512, 256, -123, -548,
		-912, -1102, -1021, -610, 131, 1141, 2302, 3458, 4439, 5097,
		5328, 5097, 4439, 3458, 2302, 1141, 131, -610, -1021, -1102,
		-912, -548, -123, 256, 512, 605, 539, 354, 111, -125,
		-299, -377, -354, -248, -96, 60, 182, 244, 240, 177,
		79, -25, -111, -158, -162, -125, -63, 7, 66, 101,
		107, 86, 47, 2, -37, -62, -69, -57, -34, -6,
		20, 37, 42, 37, 23, 6, -10, -21, -25, -22,
		-15, -5, 4, 11, 14, 13, 9, 3, -2, -5,
		-7, -7, -5, -2, 0, 2, 3, 3, 2, 1,
		0, -1, -1, -1, -1, -1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B2[201] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, -1, -1, -1, 0, 1, 2, 1, 0, -1,
		0, 0, 0, -2, -5, -6, -3, 4, 10, 11,
		6, -2, -6, -3, 1, -1, -11, -22, -21, -2,
		26, 45, 38, 10, -20, -29, -15, 0, -8, -39,
		-63, -44, 25, 105, 135, 87, -11, -88, -94, -42,
		-1, -26, -99, -133, -48, 139, 304, 312, 129, -129,
		-282, -241, -83, 14, -56, -206, -221, 40, 471, 755,
		613, 63, -549, -805, -567, -109, 118, -85, -425, -329,
		506, 1693, 2280, 1443, -754, -3153, -4152, -2814, 357, 3589,
		4944, 3589, 357, -2814, -4152, -3153, -754, 1443, 2280, 1693,
		506, -329, -425, -85, 118, -109, -567, -805, -549, 63,
		613, 755, 471, 40, -221, -206, -56, 14, -83, -241,
		-282, -129, 129, 312, 304, 139, -48, -133, -99, -26,
		-1, -42, -94, -88, -11, 87, 135, 105, 25, -44,
		-63, -39, -8, 0, -15, -29, -20, 10, 38, 45,
		26, -2, -21, -22, -11, -1, 1, -3, -6, -2,
		6, 11, 10, 4, -3, -6, -5, -2, 0, 0,
		0, -1, 0, 1, 2, 1, 0, -1, -1, -1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B3[201] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, -1,
		-1, 0, 1, 0, -1, -1, 0, 1, 0, 0,
		1, 1, -3, -4, 0, 7, 6, -5, -11, -4,
		9, 10, 0, -6, -2, -1, -7, -5, 15, 25,
		-2, -41, -34, 23, 59, 21, -44, -50, 2, 33,
		14, 0, 22, 16, -54, -93, 4, 147, 123, -82,
		-212, -77, 154, 180, -5, -124, -58, 10, -45, -44,
		149, 268, -8, -428, -368, 237, 633, 239, -466, -563,
		8, 414, 216, -54, 70, 115, -414, -804, 11, 1407,
		1301, -852, -2518, -1069, 2216, 3116, -11, -3494, -2760, 1529,
		4016, 1529, -2760, -3494, -11, 3116, 2216, -1069, -2518, -852,
		1301, 1407, 11, -804, -414, 115, 70, -54, 216, 414,
		8, -563, -466, 239, 633, 237, -368, -428, -8, 268,
		149, -44, -45, 10, -58, -124, -5, 180, 154, -77,
		-212, -82, 123, 147, 4, -93, -54, 16, 22, 0,
		14, 33, 2, -50, -44, 21, 59, 23, -34, -41,
		-2, 25, 15, -5, -7, -1, -2, -6, 0, 10,
		9, -4, -11, -5, 6, 7, 0, -4, -3, 1,
		1, 0, 0, 1, 0, -1, -1, 0, 1, 0,
		-1, -1, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B4[201]={
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, -1, -1, 1, 1, -1, -2, 1, 3,
		-1, -5, 0, 6, 2, -7, -3, 8, 6, -8,
		-7, 6, 8, -4, -7, 2, 4, 0, 2, 1,
		-10, -6, 20, 15, -29, -31, 36, 53, -37, -78,
		29, 104, -13, -128, -12, 143, 44, -147, -77, 137,
		105, -113, -120, 78, 115, -41, -85, 10, 27, 0,
		54, 23, -148, -90, 242, 206, -316, -371, 350, 576,
		-323, -804, 223, 1031, -42, -1228, -216, 1366, 537, -1420,
		-895, 1372, 1260, -1215, -1594, 955, 1863, -610, -2037, 210,
		2097, 210, -2037, -610, 1863, 955, -1594, -1215, 1260, 1372,
		-895, -1420, 537, 1366, -216, -1228, -42, 1031, 223, -804,
		-323, 576, 350, -371, -316, 206, 242, -90, -148, 23,
		54, 0, 27, 10, -85, -41, 115, 78, -120, -113,
		105, 137, -77, -147, 44, 143, -12, -128, -13, 104,
		29, -78, -37, 53, 36, -31, -29, 15, 20, -6,
		-10, 1, 2, 0, 4, 2, -7, -4, 8, 6,
		-7, -8, 6, 8, -3, -7, 2, 6, 0, -5,
		-1, 3, 1, -2, -1, 1, 1, -1, -1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B5[201]={
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, -1, 1, 1, -1, -1, 2, 1, -3,
		-1, 5, 0, -6, 2, 7, -3, -8, 6, 8,
		-7, -6, 8, 4, -7, -2, 4, 0, 2, -1,
		-10, 6, 20, -15, -29, 31, 36, -53, -37, 78,
		29, -104, -13, 128, -12, -143, 44, 147, -77, -137,
		105, 113, -120, -78, 115, 41, -85, -10, 27, 0,
		54, -23, -148, 90, 242, -206, -316, 371, 350, -576,
		-323, 804, 223, -1031, -42, 1228, -216, -1366, 537, 1420,
		-895, -1372, 1260, 1215, -1594, -955, 1863, 610, -2037, -210,
		2097, -210, -2037, 610, 1863, -955, -1594, 1215, 1260, -1372,
		-895, 1420, 537, -1366, -216, 1228, -42, -1031, 223, 804,
		-323, -576, 350, 371, -316, -206, 242, 90, -148, -23,
		54, 0, 27, -10, -85, 41, 115, -78, -120, 113,
		105, -137, -77, 147, 44, -143, -12, 128, -13, -104,
		29, 78, -37, -53, 36, 31, -29, -15, 20, 6,
		-10, -1, 2, 0, 4, -2, -7, 4, 8, -6,
		-7, 8, 6, -8, -3, 7, 2, -6, 0, 5,
		-1, -3, 1, 2, -1, -1, 1, 1, -1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B6[201]={
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		-1, 0, 1, 0, -1, 1, 0, -1, 0, 0,
		1, -1, -3, 4, 0, -7, 6, 5, -11, 4,
		9, -10, 0, 6, -2, 1, -7, 5, 15, -25,
		-2, 41, -34, -23, 59, -21, -44, 50, 2, -33,
		14, 0, 22, -16, -54, 93, 4, -147, 123, 82,
		-212, 77, 154, -180, -5, 124, -58, -10, -45, 44,
		149, -268, -8, 428, -368, -237, 633, -239, -466, 563,
		8, -414, 216, 54, 70, -115, -414, 804, 11, -1407,
		1301, 852, -2518, 1069, 2216, -3116, -11, 3494, -2760, -1529,
		4016, -1529, -2760, 3494, -11, -3116, 2216, 1069, -2518, 852,
		1301, -1407, 11, 804, -414, -115, 70, 54, 216, -414,
		8, 563, -466, -239, 633, -237, -368, 428, -8, -268,
		149, 44, -45, -10, -58, 124, -5, -180, 154, 77,
		-212, 82, 123, -147, 4, 93, -54, -16, 22, 0,
		14, -33, 2, 50, -44, -21, 59, -23, -34, 41,
		-2, -25, 15, 5, -7, 1, -2, 6, 0, -10,
		9, 4, -11, 5, 6, -7, 0, 4, -3, -1,
		1, 0, 0, -1, 0, 1, -1, 0, 1, 0,
		-1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B7[201]={
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, -1, 1, 0, -1, 2, -1, 0, 1,
		0, 0, 0, 2, -5, 6, -3, -4, 10, -11,
		6, 2, -6, 3, 1, 1, -11, 22, -21, 2,
		26, -45, 38, -10, -20, 29, -15, 0, -8, 39,
		-63, 44, 25, -105, 135, -87, -11, 88, -94, 42,
		-1, 26, -99, 133, -48, -139, 304, -312, 129, 129,
		-282, 241, -83, -14, -56, 206, -221, -40, 471, -755,
		613, -63, -549, 805, -567, 109, 118, 85, -425, 329,
		506, -1693, 2280, -1443, -754, 3153, -4152, 2814, 357, -3589,
		4944, -3589, 357, 2814, -4152, 3153, -754, -1443, 2280, -1693,
		506, 329, -425, 85, 118, 109, -567, 805, -549, -63,
		613, -755, 471, -40, -221, 206, -56, -14, -83, 241,
		-282, 129, 129, -312, 304, -139, -48, 133, -99, 26,
		-1, 42, -94, 88, -11, -87, 135, -105, 25, 44,
		-63, 39, -8, 0, -15, 29, -20, -10, 38, -45,
		26, 2, -21, 22, -11, 1, 1, 3, -6, 2,
		6, -11, 10, -4, -3, 6, -5, 2, 0, 0,
		0, 1, 0, -1, 2, -1, 0, 1, -1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};

Int16 B8[201]={
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, -1, 1, -1, 1,
		0, -1, 2, -3, 3, -2, 0, 2, -5, 7,
		-7, 5, -2, -3, 9, -13, 14, -11, 4, 5,
		-15, 22, -25, 21, -10, -6, 23, -37, 42, -37,
		20, 6, -34, 57, -69, 62, -37, -2, 47, -86,
		107, -101, 66, -7, -63, 125, -162, 158, -111, 25,
		79, -177, 240, -244, 182, -60, -96, 248, -354, 377,
		-299, 125, 111, -354, 539, -605, 512, -256, -123, 548,
		-912, 1102, -1021, 610, 131, -1141, 2302, -3458, 4439, -5097,
		5328, -5097, 4439, -3458, 2302, -1141, 131, 610, -1021, 1102,
		-912, 548, -123, -256, 512, -605, 539, -354, 111, 125,
		-299, 377, -354, 248, -96, -60, 182, -244, 240, -177,
		79, 25, -111, 158, -162, 125, -63, -7, 66, -101,
		107, -86, 47, -2, -37, 62, -69, 57, -34, 6,
		20, -37, 42, -37, 23, -6, -10, 21, -25, 22,
		-15, 5, 4, -11, 14, -13, 9, -3, -2, 5,
		-7, 7, -5, 2, 0, -2, 3, -3, 2, -1,
		0, 1, -1, 1, -1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0
};
