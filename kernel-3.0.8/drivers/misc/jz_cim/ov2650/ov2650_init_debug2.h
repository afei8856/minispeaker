#define SENSOR_WRITE_DELAY 0xffff

unsigned short ov2650_init_table[][2] = {
    {0x3012,0x80},
    {SENSOR_WRITE_DELAY, 0x0a},
    {0x308c,0x80},
    {0x308d,0x0e},
    {0x360b,0x00},
    {0x30b0,0xff},
    {0x30b1,0xff},
    {0x30b2,0x24},
    {0x300e,0x34},
    {0x300f,0xa6},
    {0x3010,0x81},
    {0x3082,0x01},
    {0x30f4,0x01},
    {0x3090,0x33},
    {0x3091,0xc0},
    {0x30ac,0x42},
    {0x30d1,0x08},
    {0x30a8,0x56},
    {0x3015,0x03},
    {0x3093,0x00},
    {0x307e,0xe5},
    {0x3079,0x00},
    {0x30aa,0x42},
    {0x3017,0x40},
    {0x30f3,0x82},
    {0x306a,0x0c},
    {0x306d,0x00},
    {0x336a,0x3c},
    {0x3076,0x6a},
    {0x30d9,0x95},
    {0x3016,0x82},
    {0x3601,0x30},
    {0x304e,0x88},
    {0x30f1,0x82},
    {0x306f,0x14},
    {0x302a,0x02},
    {0x302b,0x6a},
    {0x3012,0x10},
    {0x3011,0x01},
    {0x3013,0xf7},
    {0x301c,0x13},
    {0x301d,0x17},
    {0x3070,0x5d},
    {0x3072,0x4d},
    {0x30af,0x00},
    {0x3048,0x1f},
    {0x3049,0x4e},
    {0x304a,0x20},
    {0x304f,0x20},
    {0x304b,0x02},
    {0x304c,0x00},
    {0x304d,0x02},
    {0x304f,0x20},
    {0x30a3,0x10},
    {0x3013,0xf7},
    {0x3014,0x44},
    {0x3071,0x00},
    {0x3070,0x5d},
    {0x3073,0x00},
    {0x3072,0x4d},
    {0x301c,0x05},
    {0x301d,0x06},
    {0x304d,0x42},
    {0x304a,0x40},
    {0x304f,0x40},
    {0x3095,0x07},
    {0x3096,0x16},
    {0x3097,0x1d},
    {0x300e,0x38},
    {0x3020,0x01},
    {0x3021,0x18},
    {0x3022,0x00},
    {0x3023,0x06},
    {0x3024,0x06},
    {0x3025,0x58},
    {0x3026,0x02},
    {0x3027,0x61},
    {0x3088,0x03},
    {0x3089,0x20},
    {0x308a,0x02},
    {0x308b,0x58},
    {0x3316,0x64},
    {0x3317,0x25},
    {0x3318,0x80},
    {0x3319,0x08},
    {0x331a,0x64},
    {0x331b,0x4b},
    {0x331c,0x00},
    {0x331d,0x38},
    {0x3100,0x00},

    {0x3320,0xfa},
    {0x3321,0x11},
    {0x3322,0x92},
    {0x3323,0x01},
    {0x3324,0x97},
    {0x3325,0x02},
    {0x3326,0xff},
    {0x3327,0x0c},
    {0x3328,0x10},
    {0x3329,0x10},
    {0x332a,0x58},
    {0x332b,0x50},
    {0x332c,0xbe},
    {0x332d,0xe1},
    {0x332e,0x43},
    {0x332f,0x36},
    {0x3330,0x4d},
    {0x3331,0x44},
    {0x3332,0xf8},
    {0x3333,0x0a},
    {0x3334,0xf0},
    {0x3335,0xf0},
    {0x3336,0xf0},
    {0x3337,0x40},
    {0x3338,0x40},
    {0x3339,0x40},
    {0x333a,0x00},
    {0x333b,0x00},
    {0x3380,0x28},
    {0x3381,0x48},
    {0x3382,0x10},
    {0x3383,0x23},
    {0x3384,0xc0},
    {0x3385,0xe5},
    {0x3386,0xc2},
    {0x3387,0xb3},
    {0x3388,0x0e},
    {0x3389,0x98},
    {0x338a,0x01},
    {0x3340,0x0e},
    {0x3341,0x1a},
    {0x3342,0x31},
    {0x3343,0x45},
    {0x3344,0x5a},
    {0x3345,0x69},
    {0x3346,0x75},
    {0x3347,0x7e},
    {0x3348,0x88},
    {0x3349,0x96},
    {0x334a,0xa3},
    {0x334b,0xaf},
    {0x334c,0xc4},
    {0x334d,0xd7},
    {0x334e,0xe8},
    {0x334f,0x20},
    {0x3350,0x32},
    {0x3351,0x25},
    {0x3352,0x80},
    {0x3353,0x1e},
    {0x3354,0x00},
    {0x3355,0x85},
    {0x3356,0x32},
    {0x3357,0x25},
    {0x3358,0x80},
    {0x3359,0x1b},
    {0x335a,0x00},
    {0x335b,0x85},
    {0x335c,0x32},
    {0x335d,0x25},
    {0x335e,0x80},
    {0x335f,0x1b},
    {0x3360,0x00},
    {0x3361,0x85},
    {0x3363,0x70},
    {0x3364,0x7f},
    {0x3365,0x00},
    {0x3366,0x00},
    {0x3301,0xff},
    {0x338b,0x11},
    {0x338c,0x10},
    {0x338d,0x40},
    {0x3370,0xd0},
    {0x3371,0x00},
    {0x3372,0x00},
    {0x3373,0x40},
    {0x3374,0x10},
    {0x3375,0x10},
    {0x3376,0x04},
    {0x3377,0x00},
    {0x3378,0x04},
    {0x3379,0x80},
    {0x3069,0x84},
    {0x307c,0x10},
    {0x3087,0x02},
    {0x3300,0xfc},
    {0x3302,0x11},
    {0x3400,0x03},
    {0x3606,0x20},
    {0x3601,0x30},
    {0x300e,0x34},
    {0x3011,0x00},
    {0x30f3,0x83},
    {0x304e,0x88},
    {0x3090,0x03},
    {0x30aa,0x32},
    {0x30a3,0x80},
    {0x30a1,0x41},
    {0x363b,0x01},
    {0x363c,0xf2},
    {0x3086,0x0f},
    {0x3086,0x00},
    {SENSOR_WRITE_DELAY, 150}, 
};
