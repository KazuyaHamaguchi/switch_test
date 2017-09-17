#include <ros/ros.h>		//ROSに必要な関数を取り込むため必須！
#include <pigpiod_if2.h>	//ラズパイのピンにアクセスするためのライブラリ「PIGPIO」関数を取り込む

int main(int argc, char **argv)	//int main(void)だとROSの関数が使えない
{
        ros::init(argc, argv, "switch_test_node");	//ノード名の初期化「ros::init(argc, argv, "起動時に指定するノード名");」(必須！)
	ros::NodeHandle nh;	//ROSシステムとの通信のためのノードハンドルを宣言（必須！）
	int pi = pigpio_start(0, 0);	//PIGPIOを使うときは必ず宣言
	set_pull_up_down(pi, 22, PI_PUD_DOWN);	//GPIOピンのプルアップ・プルダウン設定「set_pull_up_down(pi, "ピン番号", "PI_PUD_DOWNかPI_PUD_UP");」
	while(ros::ok())	//ctrl + Cが押されるまで繰り返す
	{
		if(gpio_read(pi, 22) == 1)
		{
			ROS_INFO("ON");     //C言語でいうprintf「ROS_INFO("~");　""内の文字を出力」	
		}
		else
		{
			ROS_INFO("OFF");     //C言語でいうprintf「ROS_INFO("~");　""内の文字を出力」
		}
	//	time_sleep(0.1);		//delay関数「time_sleep("秒");」
	}
	pigpio_stop(pi);	//PIGPIOデーモンとの接続を終了しライブラリが使用するリソースを解放(PIGPIOを使うときは必ず宣言)
	return 0;	
}
