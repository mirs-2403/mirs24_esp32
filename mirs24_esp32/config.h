//エンコーダ用
#define PIN_ENC_A_L 39
#define PIN_ENC_B_L 36
#define PIN_ENC_A_R 35
#define PIN_ENC_B_R 34

//足回り用
#define PIN_DIR_R   25
#define PIN_PWM_R   26
#define PIN_DIR_L   32
#define PIN_PWM_L   33

//ジャッキ用モーター
#define PIN_DIR_JACK 18
#define PIN_PWM_JACK 19
#define PIN_ENC_JACK_A 13
#define PIN_ENC_JACK_B 21

//ジャッキ用リミットスイッチ
#define PIN_SW_UP 16
#define PIN_SW_DOWN 17

//ジャッキ台形制御用パラメータ
#define NEAR_END 2000


//バッテリー用
#define PIN_BATT_1  27
#define PIN_BATT_2  4

//絶対に設定しろ!!!!!!!
#define ROS_DOMAIN_ID 90

//足回り速度制御用
double RKP = 80.0;
double RKI = 30.0;
double RKD = 8.0;
double LKP = 100.0;
double LKI = 30.0;
double LKD = 8.0;

//車体数値
#define COUNTS_PER_REV    4096.0
double WHEEL_RADIUS = 0.04;  //ホイール径
double WHEEL_BASE = 0.38;  //車輪間幅

// PWM設定
const int32_t r_Channel = 0;        // PWMチャンネル
const int32_t l_Channel = 1;
const int32_t jack_Channel = 2;
const int32_t pwmFrequency = 5000; // PWM周波数 (5kHz)
const int32_t pwmResolution = 8;   // PWM分解能 (8ビット = 0-255)
