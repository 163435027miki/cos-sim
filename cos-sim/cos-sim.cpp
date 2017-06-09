#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム
#include<math.h>
#include<time.h>//時間を用いる
#include <direct.h>//フォルダを作成す
#include<stdio.h>
#include <windows.h>

#define PI 3.14159265

using namespace std;



int main(){
//////////////////定義///////////////////////////////////////////////////////////////////////////////////////////
	double Rvector[10][10];
	double V0[255];
	double V45[255];
	double V90[255];
	double V135[255];
	double V180[255];
	double V225[255];
	double V270[255];
	double V315[255];

	char inputdate_directory[255];					//inputdateの場所
	char inputrvector_directory[128];				//Rvectorの場所

	char *Input_Rvectormagniname_s = "\\Rvector_magni.csv";	//基準ベクトルの倍率
	char *Input_Rvectorname1_s = "\\Rvector0.csv";			//基準ベクトル名の指定
	char *Input_Rvectorname2_s = "\\Rvector45.csv";
	char *Input_Rvectorname3_s = "\\Rvector90.csv";
	char *Input_Rvectorname4_s = "\\Rvector135.csv";
	char *Input_Rvectorname5_s = "\\Rvector180.csv";
	char *Input_Rvectorname6_s = "\\Rvector225.csv";
	char *Input_Rvectorname7_s = "\\Rvector270.csv";
	char *Input_Rvectorname8_s = "\\Rvector315.csv";
	

	char *Input_Filename1_s = "\\V(0).csv";			//入力ファイル名の指定
	char *Input_Filename2_s = "\\V(45).csv";
	char *Input_Filename3_s = "\\V(90).csv";
	char *Input_Filename4_s = "\\V(135).csv";
	char *Input_Filename5_s = "\\V(180).csv";
	char *Input_Filename6_s = "\\V(225).csv";
	char *Input_Filename7_s = "\\V(270).csv";
	char *Input_Filename8_s = "\\V(315).csv";
	
	char *math_name1_s = "innerp.csv";				//出力結果のファイル名の指定
	char *math_name2_s = "V_sqrt.csv";
	char *math_name3_s = "Cos_similarity.csv";
	char *math_name4_s = "Angle.csv";
	char *math_name5_s = "threshold_high.csv";
	char *math_name6_s = "use_Rvector_flag.csv";
	char *math_name7_s = "use_Rvector_number.csv";
	char *math_name8_s = "threshold2.csv";
	char *math_name9_s = "threshold_low.csv";
	//char *math_name10_s = "Correction_flag.csv";
	//char *math_name11_s = "newfunction.csv";						//出力増やす用1/7

	char Input_Rvectormagni_name[255];
	char Input_Rvectorname1[255];					//基準ベクトル名・基準ベクトルの入力先の設定
	char Input_Rvectorname2[255];
	char Input_Rvectorname3[255];
	char Input_Rvectorname4[255];
	char Input_Rvectorname5[255];
	char Input_Rvectorname6[255];
	char Input_Rvectorname7[255];
	char Input_Rvectorname8[255];

	char Input_Filename1[255];						//入力ファイル名・入力元の設定
	char Input_Filename2[255];
	char Input_Filename3[255];
	char Input_Filename4[255];
	char Input_Filename5[255];
	char Input_Filename6[255];
	char Input_Filename7[255];
	char Input_Filename8[255];

													//出力ファイル名・出力先の設定
	char math_name1[64];							//内積						
	char math_name2[64];							//応答電圧Vの大きさ
	char math_name3[64];							//cos類似度
	char math_name4[64];							//角度．最終結果
	char math_name5[64];							//threshold_high
	char math_name6[64];							//use_Rvector_flag(応答電圧の最小の位置)
	char math_name7[64];							//use_Rvector_number(内積でしようする基準ベクトルの番号）
	char math_name8[64];							//2つの閾値を一つに
	char math_name9[64];							//threshold(use_Rvector_flagの応答電圧Vの大きさ）
	//char math_name10[64];							//Correction_flag
	//char math_name11[64];							//出力増やす用2/7
	
	double Rvectormagni[10];						//基準ベクトルの倍率		
	double innerp[255];								//内積
	double Rvector_sqrt[9];							//Rvectorの大きさ
	double Rvector_square[9][9];
	double Rvector_square_sum[9];
	int use_Rvector_flag[512];
	int use_Rvector_number;
	int threshold_high_flag[512];
	int threshold_low_flag[512];
	double threshold_high;
	double threshold_low;
	double threshold_low_abs;
	double threshold_high_abs;
	double V_sqrt[512];								//Vの大きさ
	double Cos_similarity[512];						//cos類似度
	double Angle[512];								//角度
	//int Correction_flag[255];						//修正をしたか否か
	//double Angle_accuracy[255];
	

	FILE *fp_innerp,*fp_V_sqrt,*fp_Cos_similarity,*fp_Angle,*fp_use_Rvector_flag,*fp_use_Rvector_number,*fp_threshold,*fp_threshold_high,*fp_threshold2;

	//FILE *fp_newfunction,*fp_Angle2,,*fp_Correction_flag;									//出力増やす用3

	int i=1,j=1;
	int count_small=1,count_large=1;
	int count_property=0;
	int count_Allproperty=0;
/////////////////////////////////初期設定 : input設定//////////////////////////////////////////////////////////////////

	int image_width;						//入力画像の横幅
	int image_wide;							//入力画像の横幅+1

	int direction_number;					//8方向，4方向，2方向の指定
	int curcuit_number;						//使用する回路
	int Rvector_number;						//使用する基準ベクトルの数
	int minor_flag;							//十字以外の変な基準ベクトルを取るときに1にする
	int All_property[10];					//上記の情報を読み込む用



	//propertyファイルの読み込み指定
    std::ifstream propety_dire("..\\property\\simulation17-0519\\property_100k.txt");		//ここだけ入力すればよい


    char propety[255];
	char Allpropety[255];
	char inputdate_directory1[255];
	char inputdate_directory2[255];
	char inputdate_directory3[255];
	char inputdate_directory4[255];
	char inputdate_directory5[255];
	char inputdate_directory6[255];			//繰返し数を増やしたい1/4


	//プロパティtxtファイルの読み込み
    if (propety_dire.fail())
    {
        printf("propertyテキストを読み取ることができません\n");
        return -1;
    }
    while (propety_dire.getline(propety, 256 - 1))
    {

		if(count_property==0)sprintf(Allpropety,propety);
		if(count_property==1)sprintf(inputrvector_directory,propety);
		if(count_property==2)sprintf(inputdate_directory1,propety);
		if(count_property==3)sprintf(inputdate_directory2,propety);
		if(count_property==4)sprintf(inputdate_directory3,propety);
		if(count_property==5)sprintf(inputdate_directory4,propety);
		if(count_property==6)sprintf(inputdate_directory5,propety);
		if(count_property==7)sprintf(inputdate_directory6,propety);			//繰返し数を増やしたい2/4

		++count_property;
    }

	//プロパティtxtファイルの一行目を文字列から数値に変換して関数に代入
	std::string tmp_Allpropety;
	std::istringstream stream_Allpropety(Allpropety);
	while(getline(stream_Allpropety,tmp_Allpropety,',')){

		int All_tmp_property=stof(tmp_Allpropety); //stof(string str) : stringをintに変換
		All_property[count_Allproperty]=All_tmp_property;

		if(count_Allproperty==0)image_width=All_property[count_Allproperty];
		if(count_Allproperty==1)direction_number=All_property[count_Allproperty];
		if(count_Allproperty==2)curcuit_number=All_property[count_Allproperty];
		if(count_Allproperty==3)Rvector_number=All_property[count_Allproperty];
		if(count_Allproperty==4)minor_flag=All_property[count_Allproperty];

		++count_Allproperty;
	}

	image_wide=image_width+1;				//入力画像の横幅+1
	/*
	printf("direction_number=%d\n",direction_number);
	printf("curcuit_number=%d\n",curcuit_number);
	printf("Rvector_number=%d\n",Rvector_number);
	printf("minor_flag=%d\n",minor_flag);*/

	
	for(int repeat=0;repeat<6;++repeat){			//繰返し数を増やしたい3/4

	/*inputdateの手動指定
	sprintf(inputrvector_directory,"..\\Rvector\\8direction_Rs=1k_under");				//inputするRvectorフォルダ指定
	if(repeat==0)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd0");		//inputする畳み込みデータのフォルダ指定
	if(repeat==1)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd10");	//inputする畳み込みデータのフォルダ指定
	if(repeat==2)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd20");	//inputする畳み込みデータのフォルダ指定
	if(repeat==3)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd30");	//inputする畳み込みデータのフォルダ指定
	if(repeat==4)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd40");	//inputする畳み込みデータのフォルダ指定
	if(repeat==5)sprintf(inputdate_directory,"..\\inputdate\\Simulation16-0802\\8方向\\conv15_8dire_enza_sd50");	//inputする畳み込みデータのフォルダ指定
	*/

	if(repeat==0)sprintf(inputdate_directory,inputdate_directory1);	//inputする畳み込みデータのフォルダ指定
	if(repeat==1)sprintf(inputdate_directory,inputdate_directory2);	//inputする畳み込みデータのフォルダ指定
	if(repeat==2)sprintf(inputdate_directory,inputdate_directory3);	//inputする畳み込みデータのフォルダ指定
	if(repeat==3)sprintf(inputdate_directory,inputdate_directory4);	//inputする畳み込みデータのフォルダ指定
	if(repeat==4)sprintf(inputdate_directory,inputdate_directory5);	//inputする畳み込みデータのフォルダ指定
	if(repeat==5)sprintf(inputdate_directory,inputdate_directory6);	//inputする畳み込みデータのフォルダ指定			//繰返し数を増やしたい4/4
	printf("repeat = %d\n",repeat);
	printf("%s\n",inputdate_directory);
	
/////////////////////////////////準備/////////////////////////////////////////////////////////////////////////////////////
	//実行日時の表示
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	char date[128]="";
	sprintf(date,"%2d/%2d/%2d - %d:%d:%d\n",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	printf(date);

	//結果を保存するフォルダの生成
	//フォルダ名は実行日時になる
	char date_directory[128];
	sprintf(date_directory,"..\\result_inu\\%2d-%02d%02d-%02d%02d%02d\\",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	 if(_mkdir(date_directory)==0){
        printf("フォルダ %s を作成しました\n",date_directory);
    }else{
        printf("フォルダ作成に失敗しました。\n");
    }

	
////////////////////////////入出力ディレクトリの作成(C式のため汚い)//////////////////////////////////////////////////////////////////////////////
	//Rvector
	strcpy(Input_Rvectormagni_name, inputrvector_directory);
	strcat(Input_Rvectormagni_name, Input_Rvectormagniname_s);
	strcpy(Input_Rvectorname1, inputrvector_directory);
    strcat(Input_Rvectorname1, Input_Rvectorname1_s);
	strcpy(Input_Rvectorname2, inputrvector_directory);
    strcat(Input_Rvectorname2, Input_Rvectorname2_s);
	strcpy(Input_Rvectorname3, inputrvector_directory);
    strcat(Input_Rvectorname3, Input_Rvectorname3_s);
	strcpy(Input_Rvectorname4, inputrvector_directory);
    strcat(Input_Rvectorname4, Input_Rvectorname4_s);
	strcpy(Input_Rvectorname5, inputrvector_directory);
    strcat(Input_Rvectorname5, Input_Rvectorname5_s);
	strcpy(Input_Rvectorname6, inputrvector_directory);
    strcat(Input_Rvectorname6, Input_Rvectorname6_s);
	strcpy(Input_Rvectorname7, inputrvector_directory);
    strcat(Input_Rvectorname7, Input_Rvectorname7_s);
	strcpy(Input_Rvectorname8, inputrvector_directory);
    strcat(Input_Rvectorname8, Input_Rvectorname8_s);
	
	//Input
	strcpy(Input_Filename1, inputdate_directory);
    strcat(Input_Filename1, Input_Filename1_s);
	strcpy(Input_Filename2, inputdate_directory);
    strcat(Input_Filename2, Input_Filename2_s);
	strcpy(Input_Filename3, inputdate_directory);
    strcat(Input_Filename3, Input_Filename3_s);
	strcpy(Input_Filename4, inputdate_directory);
    strcat(Input_Filename4, Input_Filename4_s);
	strcpy(Input_Filename5, inputdate_directory);
    strcat(Input_Filename5, Input_Filename5_s);
	strcpy(Input_Filename6, inputdate_directory);
    strcat(Input_Filename6, Input_Filename6_s);
	strcpy(Input_Filename7, inputdate_directory);
    strcat(Input_Filename7, Input_Filename7_s);
	strcpy(Input_Filename8, inputdate_directory);
    strcat(Input_Filename8, Input_Filename8_s);

	//Output
	strcpy(math_name1, date_directory);
    strcat(math_name1, math_name1_s);
	strcpy(math_name2, date_directory);
    strcat(math_name2, math_name2_s);
	strcpy(math_name3, date_directory);
    strcat(math_name3, math_name3_s);
	strcpy(math_name4, date_directory);
    strcat(math_name4, math_name4_s);
	strcpy(math_name5, date_directory);
	strcat(math_name5, math_name5_s);
	strcpy(math_name6, date_directory);
    strcat(math_name6, math_name6_s);
	strcpy(math_name7, date_directory);
    strcat(math_name7, math_name7_s);
	strcpy(math_name8, date_directory);
    strcat(math_name8, math_name8_s);
	strcpy(math_name9, date_directory);
    strcat(math_name9, math_name9_s);
	//strcpy(math_name10, date_directory);
    //strcat(math_name10, math_name10_s);

	//strcpy(math_name11, date_directory);					//出力増やす用4/7
    //strcat(math_name11, math_name11_s);

////////////////////////////ファイルの読み込み//////////////////////////////////////////////////////////////////////////////

    //Rvector
	ifstream Rvector_magni(Input_Rvectormagni_name);
	ifstream Rvector_0(Input_Rvectorname1);
	ifstream Rvector_45(Input_Rvectorname2);
	ifstream Rvector_90(Input_Rvectorname3);
	ifstream Rvector_135(Input_Rvectorname4);
	ifstream Rvector_180(Input_Rvectorname5);
	ifstream Rvector_225(Input_Rvectorname6);
	ifstream Rvector_270(Input_Rvectorname7);
	ifstream Rvector_315(Input_Rvectorname8);

	//Input
	ifstream V_0(Input_Filename1);
	ifstream V_45(Input_Filename2);
	ifstream V_90(Input_Filename3);
	ifstream V_135(Input_Filename4);
	ifstream V_180(Input_Filename5);
	ifstream V_225(Input_Filename6);
	ifstream V_270(Input_Filename7);
	ifstream V_315(Input_Filename8);
	

////////////////////////エラー出力/////////////////////////////////////////////////////////////////////////////////////////////
	if(!Rvector_magni){cout<<"入力エラー Rvector_magni.csvがありません";return 1;}
    if(!Rvector_0){cout<<"入力エラー Rvector0.csvがありません";return 1;}
	if(!Rvector_45){cout<<"入力エラー Rvector45.csvがありません";return 1;}
	if(!Rvector_90){cout<<"入力エラー Rvector90.csvがありません";return 1;}
	if(!Rvector_135){cout<<"入力エラー Rvector135.csvがありません";return 1;}
	if(!Rvector_180){cout<<"入力エラー Rvector180.csvがありません";return 1;}
	if(!Rvector_225){cout<<"入力エラー Rvector225.csvがありません";return 1;}
	if(!Rvector_270){cout<<"入力エラー Rvector270.csvがありません";return 1;}
	if(!Rvector_315){cout<<"入力エラー Rvector315.csvがありません";return 1;}	
	if(!V_0){cout<<"入力エラー V(0).csvがありません";return 1;}
	if(!V_45){cout<<"入力エラー V(45).csvがありません";return 1;}
	if(!V_90){cout<<"入力エラー V(90).csvがありません";return 1;}
	if(!V_135){cout<<"入力エラー V(135).csvがありません";return 1;}
	if(!V_180){cout<<"入力エラー V(180).csvがありません";return 1;}
	if(!V_225){cout<<"入力エラー V(225).csvがありません";return 1;}
	if(!V_270){cout<<"入力エラー V(270).csvがありません";return 1;}
	if(!V_315){cout<<"入力エラー V(315).csvがありません";return 1;}
	
	
/////////////////////////出力ファイルを開く///////////////////////////////////////////////////////////////////////////////////
	if((fp_innerp=fopen(math_name1,"w"))==NULL){cout<<"入力エラー innerp.csvが開けません";exit(1);}
	if((fp_V_sqrt=fopen(math_name2,"w"))==NULL){cout<<"入力エラー V_sqrt.csvが開けません";exit(1);}
	if((fp_Cos_similarity=fopen(math_name3,"w"))==NULL){cout<<"入力エラー Cos_similarity.csvが開けません";exit(1);}
	if((fp_Angle=fopen(math_name4,"w"))==NULL){cout<<"入力エラー Angle.csvが開けません";exit(1);}
	if((fp_threshold_high=fopen(math_name5,"w"))==NULL){cout<<"入力エラー threshold_high.csvが開けません";exit(1);}
	if((fp_use_Rvector_flag=fopen(math_name6,"w"))==NULL){cout<<"入力エラー use_Rvector_flag.csvが開けません";exit(1);}
	if((fp_use_Rvector_number=fopen(math_name7,"w"))==NULL){cout<<"入力エラー use_Rvector_number.csvが開けません";exit(1);}
	if((fp_threshold2=fopen(math_name8,"w"))==NULL){cout<<"入力エラー threshold2.csvが開けません";exit(1);}
	if((fp_threshold=fopen(math_name9,"w"))==NULL){cout<<"入力エラー threshold.csvが開けません";exit(1);}
	//if((fp_Correction_flag=fopen(math_name10,"w"))==NULL){cout<<"入力エラー Correction_flag.csvが開けません";exit(1);}
	//if((fp_newfanction=fopen(math_name11,"w"))==NULL){cout<<"入力エラー newfunction.csvが開けません";exit(1);}	//出力増やす用5/7

	string str_Rvector_magni;
	while (getline(Rvector_magni,str_Rvector_magni)){
		string token_Rvector_magni;
		istringstream stream(str_Rvector_magni);
		while(getline(stream,token_Rvector_magni,',')){
			double temp_Rvector_magni=stof(token_Rvector_magni); //stof(string str) : stringをfloatに変換
			Rvectormagni[i]=temp_Rvector_magni;
			i++;
		}
	}


	

////////////////////////////////////////Rvectorの読み取り////////////////////////////////////////////////
if(repeat==0){

i=1;
 string str_Rvector0,str_Rvector45,str_Rvector90,str_Rvector135,str_Rvector180,str_Rvector225,str_Rvector270,str_Rvector315;
   while(getline(Rvector_0,str_Rvector0)){
        string token_Rvector0;
        istringstream stream(str_Rvector0);

		getline(Rvector_45,str_Rvector45);	string token_Rvector45;	istringstream stream_Rvector45(str_Rvector45);
		getline(Rvector_90,str_Rvector90);	string token_Rvector90;	istringstream stream_Rvector90(str_Rvector90);
		getline(Rvector_135,str_Rvector135);	string token_Rvector135;	istringstream stream_Rvector135(str_Rvector135);
		getline(Rvector_180,str_Rvector180);	string token_Rvector180;	istringstream stream_Rvector180(str_Rvector180);
		getline(Rvector_225,str_Rvector225);	string token_Rvector225;	istringstream stream_Rvector225(str_Rvector225);
		getline(Rvector_270,str_Rvector270);	string token_Rvector270;	istringstream stream_Rvector270(str_Rvector270);
		getline(Rvector_315,str_Rvector315);	string token_Rvector315;	istringstream stream_Rvector315(str_Rvector315);

        //1行のうち、文字列とコンマを分割する
        while(getline(stream,token_Rvector0,',')){
            //すべて文字列として読み込まれるため
            //数値は変換が必要
            double temp_Rvecrot0=stof(token_Rvector0);	//stof(string str) : stringをfloatに変換
			Rvector[i][j]=temp_Rvecrot0;				//0度入力画像の時の値を読む
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];//倍率をかける
			Rvector_square[i][j]=pow(Rvector[i][j],2);	//基準ベクトルの2倍を求める
			i++;										//iは入力した画像の角度を番号で，jは取得位置を示す

			getline(stream_Rvector45,token_Rvector45,',');
			double tmp_Rvector45=stof(token_Rvector45);
			Rvector[i][j]=tmp_Rvector45;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;
        
			getline(stream_Rvector90,token_Rvector90,',');
			double tmp_Rvector90=stof(token_Rvector90);
			Rvector[i][j]=tmp_Rvector90;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;

			getline(stream_Rvector135,token_Rvector135,',');
			double tmp_Rvector135=stof(token_Rvector135);
			Rvector[i][j]=tmp_Rvector135;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;

			getline(stream_Rvector180,token_Rvector180,',');
			double tmp_Rvector180=stof(token_Rvector180);
			Rvector[i][j]=tmp_Rvector180;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;

			getline(stream_Rvector225,token_Rvector225,',');
			double tmp_Rvector225=stof(token_Rvector225);
			Rvector[i][j]=tmp_Rvector225;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;

			getline(stream_Rvector270,token_Rvector270,',');
			double tmp_Rvector270=stof(token_Rvector270);
			Rvector[i][j]=tmp_Rvector270;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i++;

			getline(stream_Rvector315,token_Rvector315,',');
			double tmp_Rvector315=stof(token_Rvector315);
			Rvector[i][j]=tmp_Rvector315;
			Rvector[i][j]=Rvectormagni[j]*Rvector[i][j];
			Rvector_square[i][j]=pow(Rvector[i][j],2);
			i=1;
			j++;
           
        }
	}
}
  for(i=1;i<=8;i++){
	for(j=1;j<=8;j++){
		printf("%lf, ",Rvector[i][j]);
	}printf("\n");
  }


//////////////////////Rvectorの大きさを求めている/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   if(direction_number==8){
	   for(i=1;i<=8;i++){
		Rvector_square_sum[i]=Rvector_square[i][1]+Rvector_square[i][2]+Rvector_square[i][3]+Rvector_square[i][4]+Rvector_square[i][5]+Rvector_square[i][6]+Rvector_square[i][7]+Rvector_square[i][8];
	   }
   }else{
	   if(direction_number==4){
		   for(i=1;i<=8;i++){
		   if(minor_flag==0)Rvector_square_sum[i]=Rvector_square[i][1]+Rvector_square[i][3]+Rvector_square[i][5]+Rvector_square[i][7];
		   if(minor_flag==1)Rvector_square_sum[i]=Rvector_square[i][1]+Rvector_square[i][2]+Rvector_square[i][3]+Rvector_square[i][4];//未定
		   }
	   }else{
		   if(direction_number==2){
			   for(i=1;i<=8;i++){
			    if(minor_flag==0)Rvector_square_sum[i]=Rvector_square[i][1]+Rvector_square[i][3];
				if(minor_flag==1)Rvector_square_sum[i]=Rvector_square[i][1]+Rvector_square[i][2];
			   }
		   }else{
			   cout<<"direction_numberの設定がおかしいエラー"<<endl;
			   return 1;
		   }
	   }
   }
   for(i=1;i<=8;i++){
		Rvector_sqrt[i]=sqrt(Rvector_square_sum[i]);
   }

		//Rvector_sqrt表示テスト
		//cout<<"Rvector_square_sum="<<Rvector_square_sum<<endl;
		//cout<<"Rvector_sqrt="<<Rvector_sqrt<<endl;

///////////////////////応答電圧のcsvの読み込み//////////////////////////////////////////////////////////////////////////////////////////
		i=1;
		string str_0,str_45,str_90,str_135,str_180,str_225,str_270,str_315;

		while(getline(V_0,str_0)){					//このループ内ですべてを行う
			count_small=1;count_large=1;			//初期化


///////////////いろいろ定義．ここでやらないといけない///////////////////////////////////////////////////////////////////////////
        string token_V_0;
        istringstream stream_V_0(str_0);
		
		getline(V_45,str_45);	string token_V_45;	istringstream stream_V_45(str_45);
		getline(V_90,str_90);	string token_V_90;	istringstream stream_V_90(str_90);
		getline(V_135,str_135);	string token_V_135;	istringstream stream_V_135(str_135);
		getline(V_180,str_180);	string token_V_180;	istringstream stream_V_180(str_180);
		getline(V_225,str_225);	string token_V_225;	istringstream stream_V_225(str_225);
		getline(V_270,str_270);	string token_V_270;	istringstream stream_V_270(str_270);
		getline(V_315,str_315);	string token_V_315;	istringstream stream_V_315(str_315);
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////配列に代入//////////////////////////////////////////////////////////////////////////////////////////////////

        while(getline(stream_V_0,token_V_0,',')){	//一行読み取る．V0のみ，繰り返しの範囲指定に用いる
			double tmp_V_0=stof(token_V_0);			//文字を数字に変換
			V0[count_small]=tmp_V_0;				//配列に代入
			V0[count_small]=Rvectormagni[1]*V0[count_small];

			getline(stream_V_45,token_V_45,',');
			double tmp_V_45=stof(token_V_45);
			V45[count_small]=tmp_V_45;
			V45[count_small]=Rvectormagni[2]*V45[count_small];
        
			getline(stream_V_90,token_V_90,',');
			double tmp_V_90=stof(token_V_90);
			V90[count_small]=tmp_V_90;
			V90[count_small]=Rvectormagni[3]*V90[count_small];

			getline(stream_V_135,token_V_135,',');
			double tmp_V_135=stof(token_V_135);
			V135[count_small]=tmp_V_135;
			V135[count_small]=Rvectormagni[4]*V135[count_small];

			getline(stream_V_180,token_V_180,',');
			double tmp_V_180=stof(token_V_180);
			V180[count_small]=tmp_V_180;
			V180[count_small]=Rvectormagni[5]*V180[count_small];

			getline(stream_V_225,token_V_225,',');
			double tmp_V_225=stof(token_V_225);
			V225[count_small]=tmp_V_225;
			V225[count_small]=Rvectormagni[6]*V225[count_small];

			getline(stream_V_270,token_V_270,',');
			double tmp_V_270=stof(token_V_270);
			V270[count_small]=tmp_V_270;
			V270[count_small]=Rvectormagni[7]*V270[count_small];

			getline(stream_V_315,token_V_315,',');
			double tmp_V_315=stof(token_V_315);
			V315[count_small]=tmp_V_315; 
			V315[count_small]=Rvectormagni[8]*V315[count_small];


///////////////////ここからしばらく大小判定/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////負の閾値判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////8方向取得のflag(負の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==8){
			if(V0[count_small]<=V45[count_small] && V0[count_small]<=V90[count_small] && V0[count_small]<=V135[count_small] &&
				V0[count_small]<=V180[count_small] && V0[count_small]<=V225[count_small] && V0[count_small]<=V270[count_small] && V0[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=1;}			//Vの大小比較

			if(V45[count_small]<=V0[count_small] && V45[count_small]<=V90[count_small] && V45[count_small]<=V135[count_small] &&
				V45[count_small]<=V180[count_small] && V45[count_small]<=V225[count_small] && V45[count_small]<=V270[count_small] && V45[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=2;}

			if(V90[count_small]<=V0[count_small] && V90[count_small]<=V45[count_small] && V90[count_small]<=V135[count_small] &&
				V90[count_small]<=V180[count_small] && V90[count_small]<=V225[count_small] && V90[count_small]<=V270[count_small] && V90[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=3;}

			if(V135[count_small]<=V0[count_small] && V135[count_small]<=V45[count_small] && V135[count_small]<=V90[count_small] &&
				V135[count_small]<=V180[count_small] && V135[count_small]<=V225[count_small] && V135[count_small]<=V270[count_small] && V135[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=4;}

			if(V180[count_small]<=V0[count_small] && V180[count_small]<=V45[count_small] && V180[count_small]<=V90[count_small] &&
				V180[count_small]<=V135[count_small] && V180[count_small]<=V225[count_small] && V180[count_small]<=V270[count_small] && V180[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=5;}

			if(V225[count_small]<=V0[count_small] && V225[count_small]<=V45[count_small] && V225[count_small]<=V90[count_small] &&
				V225[count_small]<=V135[count_small] && V225[count_small]<=V180[count_small] && V225[count_small]<=V270[count_small] && V225[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=6;}

			if(V270[count_small]<=V0[count_small] && V270[count_small]<=V45[count_small] && V270[count_small]<=V90[count_small] &&
				V270[count_small]<=V135[count_small] && V270[count_small]<=V180[count_small] && V270[count_small]<=V225[count_small] && V270[count_small]<=V315[count_small])
			{threshold_low_flag[count_small]=7;}

			if(V315[count_small]<=V0[count_small] && V315[count_small]<=V45[count_small] && V315[count_small]<=V90[count_small] &&
				V315[count_small]<=V135[count_small] && V315[count_small]<=V180[count_small] && V315[count_small]<=V225[count_small] && V315[count_small]<=V270[count_small])
			{threshold_low_flag[count_small]=8;}
			}

///////////////////////4方向取得のflag(負の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==4){
				if(minor_flag==0){
					if(V0[count_small]<=V90[count_small] &&	V0[count_small]<=V180[count_small] && V0[count_small]<=V270[count_small])
						{threshold_low_flag[count_small]=1;}			//Vの大小比較


					if(V90[count_small]<=V0[count_small] &&	V90[count_small]<=V180[count_small] && V90[count_small]<=V270[count_small])
						{threshold_low_flag[count_small]=3;}


					if(V180[count_small]<=V0[count_small] && V180[count_small]<=V90[count_small] &&V180[count_small]<=V270[count_small])
						{threshold_low_flag[count_small]=5;}


					if(V270[count_small]<=V0[count_small] && V270[count_small]<=V90[count_small] && V270[count_small]<=V180[count_small])
						{threshold_low_flag[count_small]=7;}

				}
				if(minor_flag==1){

							if(V0[count_small]<=V45[count_small] && V0[count_small]<=V90[count_small] && V0[count_small]<=V135[count_small])
								{threshold_low_flag[count_small]=1;}			//Vの大小比較

							if(V45[count_small]<=V0[count_small] && V45[count_small]<=V90[count_small] && V45[count_small]<=V135[count_small])
								{threshold_low_flag[count_small]=2;}

							if(V90[count_small]<=V0[count_small] && V90[count_small]<=V45[count_small] && V90[count_small]<=V135[count_small])
								{threshold_low_flag[count_small]=3;}

							if(V135[count_small]<=V0[count_small] && V135[count_small]<=V45[count_small] && V135[count_small]<=V90[count_small])
								{threshold_low_flag[count_small]=4;}

				}
			}


///////////////////////2方向取得のflag(負の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==2){


					if(minor_flag==0){
						
						if(V0[count_small]<=V90[count_small]){
							threshold_low_flag[count_small]=1;			//Vの大小比較
						}else{
							threshold_low_flag[count_small]=3;
						}
					}
					if(minor_flag==1){

						if(V0[count_small]<=V45[count_small]){
							threshold_low_flag[count_small]=1;			//Vの大小比較
						}else{
							threshold_low_flag[count_small]=2;
						}
						
					}
				
				
				//else{
					//printf("curcuit_number=%d のエラー",curcuit_number);
				//}

			}		


//////////////正の閾値の判定////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////8方向取得のflag(正の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==8){
			if(V0[count_small]>=V45[count_small] && V0[count_small]>=V90[count_small] && V0[count_small]>=V135[count_small] &&
				V0[count_small]>=V180[count_small] && V0[count_small]>=V225[count_small] && V0[count_small]>=V270[count_small] && V0[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=1;}			//Vの大小比較

			if(V45[count_small]>=V0[count_small] && V45[count_small]>=V90[count_small] && V45[count_small]>=V135[count_small] &&
				V45[count_small]>=V180[count_small] && V45[count_small]>=V225[count_small] && V45[count_small]>=V270[count_small] && V45[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=2;}

			if(V90[count_small]>=V0[count_small] && V90[count_small]>=V45[count_small] && V90[count_small]>=V135[count_small] &&
				V90[count_small]>=V180[count_small] && V90[count_small]>=V225[count_small] && V90[count_small]>=V270[count_small] && V90[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=3;}

			if(V135[count_small]>=V0[count_small] && V135[count_small]>=V45[count_small] && V135[count_small]>=V90[count_small] &&
				V135[count_small]>=V180[count_small] && V135[count_small]>=V225[count_small] && V135[count_small]>=V270[count_small] && V135[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=4;}

			if(V180[count_small]>=V0[count_small] && V180[count_small]>=V45[count_small] && V180[count_small]>=V90[count_small] &&
				V180[count_small]>=V135[count_small] && V180[count_small]>=V225[count_small] && V180[count_small]>=V270[count_small] && V180[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=5;}

			if(V225[count_small]>=V0[count_small] && V225[count_small]>=V45[count_small] && V225[count_small]>=V90[count_small] &&
				V225[count_small]>=V135[count_small] && V225[count_small]>=V180[count_small] && V225[count_small]>=V270[count_small] && V225[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=6;}

			if(V270[count_small]>=V0[count_small] && V270[count_small]>=V45[count_small] && V270[count_small]>=V90[count_small] &&
				V270[count_small]>=V135[count_small] && V270[count_small]>=V180[count_small] && V270[count_small]>=V225[count_small] && V270[count_small]>=V315[count_small])
			{threshold_high_flag[count_small]=7;}

			if(V315[count_small]>=V0[count_small] && V315[count_small]>=V45[count_small] && V315[count_small]>=V90[count_small] &&
				V315[count_small]>=V135[count_small] && V315[count_small]>=V180[count_small] && V315[count_small]>=V225[count_small] && V315[count_small]>=V270[count_small])
			{threshold_high_flag[count_small]=8;}
			}

///////////////////////4方向取得のflag(正の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==4){
				if(minor_flag==0){
					if(V0[count_small]>=V90[count_small] &&	V0[count_small]>=V180[count_small] && V0[count_small]>=V270[count_small])
						{threshold_high_flag[count_small]=1;}			//Vの大小比較


					if(V90[count_small]>=V0[count_small] &&	V90[count_small]>=V180[count_small] && V90[count_small]>=V270[count_small])
						{threshold_high_flag[count_small]=3;}


					if(V180[count_small]>=V0[count_small] && V180[count_small]>=V90[count_small] &&V180[count_small]>=V270[count_small])
						{threshold_high_flag[count_small]=5;}


					if(V270[count_small]>=V0[count_small] && V270[count_small]>=V90[count_small] && V270[count_small]>=V180[count_small])
						{threshold_high_flag[count_small]=7;}

				}
				if(minor_flag==1){

							if(V0[count_small]>=V45[count_small] && V0[count_small]>=V90[count_small] && V0[count_small]>=V135[count_small])
								{threshold_high_flag[count_small]=1;}			//Vの大小比較

							if(V45[count_small]>=V0[count_small] && V45[count_small]>=V90[count_small] && V45[count_small]>=V135[count_small])
								{threshold_high_flag[count_small]=2;}

							if(V90[count_small]>=V0[count_small] && V90[count_small]>=V45[count_small] && V90[count_small]>=V135[count_small])
								{threshold_high_flag[count_small]=3;}

							if(V135[count_small]>=V0[count_small] && V135[count_small]>=V45[count_small] && V135[count_small]>=V90[count_small])
								{threshold_high_flag[count_small]=4;}

				}
			}


///////////////////////2方向取得のflag(正の閾値)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==2){


					if(minor_flag==0){
						
						if(V0[count_small]>=V90[count_small]){
							threshold_high_flag[count_small]=1;			//Vの大小比較
						}else{
							threshold_high_flag[count_small]=3;
						}
					}
					if(minor_flag==1){

						if(V0[count_small]>=V45[count_small]){
							threshold_high_flag[count_small]=1;			//Vの大小比較
						}else{
							threshold_high_flag[count_small]=2;
						}
						
					}
				
				
				//else{
					//printf("curcuit_number=%d のエラー",curcuit_number);
				//}

			}

			count_small++;							//一行読みとったとき用のカウント

//////////////閾値判定ここまで/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////break条件を記す//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(count_small==image_wide){
				count_large++;
				break;
				}
			}
////////////////////////////計算条件//////////////////////////////////////////////////////////////////////////////////////////////

		//test
		/*cout<<"0度だぜ"<<V0[3]<<endl;
		cout<<"45度だぜ"<<V45[3]<<endl;
		cout<<"90度だぜ"<<V90[3]<<endl;
		cout<<"135度だぜ"<<V135[3]<<endl;
		cout<<"180度だぜ"<<V180[3]<<endl;
		cout<<"225度だぜ"<<V225[3]<<endl;
		cout<<"270度だぜ"<<V270[3]<<endl;
		cout<<"315度だぜ"<<V315[3]<<endl;*/
			for(j=1;j<image_wide;++j){						//一行ずつ計算する
		//cout<<"処理中"<<endl;
		//if(minor_flag==0){
			
				//ここで正負の2つの閾値を取れるように改修する
			if(threshold_low_flag[j]==1){threshold_low=V0[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==2){threshold_low=V45[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==3){threshold_low=V90[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==4){threshold_low=V135[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==5){threshold_low=V180[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==6){threshold_low=V225[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==7){threshold_low=V270[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(threshold_low_flag[j]==8){threshold_low=V315[j];fprintf(fp_threshold,"%lf,",threshold_low);}
			if(j==image_width){fprintf(fp_threshold,"\n");}


			if(threshold_high_flag[j]==1){threshold_high=V0[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==2){threshold_high=V45[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==3){threshold_high=V90[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==4){threshold_high=V135[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==5){threshold_high=V180[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==6){threshold_high=V225[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==7){threshold_high=V270[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(threshold_high_flag[j]==8){threshold_high=V315[j];fprintf(fp_threshold_high,"%lf,",threshold_high);}
			if(j==image_width){fprintf(fp_threshold_high,"\n");}

			use_Rvector_flag[j] = threshold_high_flag[j];	//基本は正の閾値を取る

			if(threshold_low<0){
				threshold_low_abs=threshold_low*-1;
			}else{
				threshold_low_abs=threshold_low;
			}
			if(threshold_high<0){
				threshold_high_abs=threshold_high*-1;
			}else{
				threshold_high_abs=threshold_high;
			}

			if(threshold_low_abs>threshold_high_abs){
				fprintf(fp_threshold2,"%lf,",threshold_low);
				if(minor_flag==1)use_Rvector_flag[j]=threshold_low_flag[j]+4;
				if(direction_number==2)use_Rvector_flag[j]=threshold_low_flag[j]+4;
			}
			else{
				fprintf(fp_threshold2,"%lf,",threshold_high);
			}

			if(j==image_width){fprintf(fp_threshold2,"\n");}

//基準を90度ずらす
				if(use_Rvector_flag[j]>=3){							//-90°を用いる
					use_Rvector_number=use_Rvector_flag[j]-2;		//90,135,180,225,270,315のとき
				}else{
					use_Rvector_number=use_Rvector_flag[j]+6;		//0,45のとき
				}
//基準を90°ずらさない
	//			use_Rvector_number=use_Rvector_flag[j];

			//printf("%d",use_Rvector_number);


//////////////ファイルへの書き込み(fp_use_Rvector_flag,fp_use_Rvector_number)/////////////////////////////////////////////
			fprintf(fp_use_Rvector_flag,"%d,",use_Rvector_flag[j]);
			if(j==image_width){fprintf(fp_use_Rvector_flag,"\n");}

			fprintf(fp_use_Rvector_number,"%d,",use_Rvector_number);
			if(j==image_width){fprintf(fp_use_Rvector_number,"\n");}


/////////////////////////計算//////////////////////////////////////////////////////////////////////////////////////////////
			if(direction_number==8){
				innerp[j] = (Rvector[use_Rvector_number][1]*V0[j]) + (Rvector[use_Rvector_number][2]*V45[j]) + (Rvector[use_Rvector_number][3]*V90[j]) + (Rvector[use_Rvector_number][4]*V135[j]) 
					+ (Rvector[use_Rvector_number][5]*V180[j]) + (Rvector[use_Rvector_number][6]*V225[j]) + (Rvector[use_Rvector_number][7]*V270[j]) + (Rvector[use_Rvector_number][8]*V315[j]);
				V_sqrt[j]=sqrt( pow(V0[j],2) + pow(V45[j],2)  + pow(V90[j],2)  + pow(V135[j],2)  + pow(V180[j],2)  + pow(V225[j],2)  + pow(V270[j],2)  + pow(V315[j],2) );
				}else{
					if(direction_number==4){
						if(minor_flag==0){
						innerp[j] = (Rvector[use_Rvector_number][1]*V0[j]) + (Rvector[use_Rvector_number][3]*V90[j]) + (Rvector[use_Rvector_number][5]*V180[j]) + (Rvector[use_Rvector_number][7]*V270[j]);
						V_sqrt[j]=sqrt( pow(V0[j],2) + pow(V90[j],2)  + pow(V180[j],2)  + pow(V270[j],2));
						}
						if(minor_flag==1){
						innerp[j] = (Rvector[use_Rvector_number][1]*V0[j]) + (Rvector[use_Rvector_number][2]*V45[j]) + (Rvector[use_Rvector_number][3]*V90[j]) + (Rvector[use_Rvector_number][4]*V135[j]);
						V_sqrt[j]=sqrt( pow(V0[j],2) + pow(V45[j],2)  + pow(V90[j],2)  + pow(V135[j],2));
						}
						}else{
							if(direction_number==2){
								if(minor_flag==0){
								innerp[j] = (Rvector[use_Rvector_number][1]*V0[j]) + (Rvector[use_Rvector_number][3]*V90[j]);
								V_sqrt[j]=sqrt( pow(V0[j],2) + pow(V90[j],2));
								}
								if(minor_flag==1){
								innerp[j] = (Rvector[use_Rvector_number][1]*V0[j]) + (Rvector[use_Rvector_number][2]*V45[j]);
								V_sqrt[j]=sqrt( pow(V0[j],2) + pow(V45[j],2));
								}
								}else{
									cout<<"direction_numberの設定がおかしいエラー"<<endl;
									return 1;
								}
						}
				}

			

/////////////////////cos類似度の計算///////////////////////////////////////////////////////////////////////////////////////////////

			Cos_similarity[j] = innerp[j] / (Rvector_sqrt[use_Rvector_number] * V_sqrt[j]);

			//基準をずらす
			if(use_Rvector_number<7){Angle[j] = acos(Cos_similarity[j])*180/PI+((use_Rvector_number-1)*45);}
			if(use_Rvector_number>6){Angle[j] = acos(Cos_similarity[j])*180/PI+((use_Rvector_number-9)*45);}

			//基準をずらさない
		//	Angle[j] = acos(Cos_similarity[j])*180/PI+((use_Rvector_number-1)*45);

			//if(Angle[j]-45*(use_Rvector_number-1)>20)Angle[j]=Angle[j]-45*(use_Rvector_number-1);
			//Angle[j] = acos(Cos_similarity[j])*180/PI;

			if(Angle[j]<0){
				Angle[j] = Angle[j] +360;
			}
/*
			Correction_flag[j]=0;//無修正の場合は0

			if(use_Rvector_flag[j]==1){
				if(Angle[j]<-180){Angle[j]=Angle[j]+360;Correction_flag[j]=101;}
				if(Angle[j]>180){Angle[j]=Angle[j]-360;Correction_flag[j]=102;}
			}
			if(use_Rvector_flag[j]==2){
				if(Angle[j]<-135){Angle[j]=Angle[j]+360;Correction_flag[j]=201;}
				if(Angle[j]>225){Angle[j]=Angle[j]-360;Correction_flag[j]=202;}
			}
			if(use_Rvector_flag[j]==3){
				if(Angle[j]<-90){Angle[j]=Angle[j]+360;Correction_flag[j]=301;}
				if(Angle[j]>270){Angle[j]=Angle[j]-360;Correction_flag[j]=302;}
			}
			if(use_Rvector_flag[j]==4){
				if(Angle[j]<-45){Angle[j]=Angle[j]+360;Correction_flag[j]=401;}
				if(Angle[j]>315){Angle[j]=Angle[j]-360;Correction_flag[j]=402;}
			}
			if(use_Rvector_flag[j]==5){
				if(Angle[j]<0){Angle[j]=Angle[j]+360;Correction_flag[j]=501;}
				if(Angle[j]>360){Angle[j]=Angle[j]-360;Correction_flag[j]=502;}
			}
			if(use_Rvector_flag[j]==6){
				if(Angle[j]<45){Angle[j]=Angle[j]+360;Correction_flag[j]=601;}
				if(Angle[j]>405){Angle[j]=Angle[j]-360;Correction_flag[j]=602;}
			}
			if(use_Rvector_flag[j]==7){
				if(Angle[j]<90){Angle[j]=Angle[j]+360;Correction_flag[j]=701;}
				if(Angle[j]>450){Angle[j]=Angle[j]-360;Correction_flag[j]=702;}
			}
			if(use_Rvector_flag[j]==8){
				
				if(Angle[j]<=135){Angle[j]=Angle[j]+360;Correction_flag[j]=801;}
				if(Angle[j]>495){Angle[j]=Angle[j]-360;Correction_flag[j]=802;}
			}
*/
			

			
		

			//計算テスト
			//cout<<"Angle="<<Angle[j]<<endl;

/////////////////////////計算終わり/////////////////////////////////////////////////////////////////////////////////////////////

///////////////////ファイルへの書き込み(一行ずつ書き込み）////////////////////////////////////////////////////////////////////////


			fprintf(fp_innerp,"%lf,",innerp[j]);
			if(j==image_width){fprintf(fp_innerp,"\n");}

			fprintf(fp_V_sqrt,"%lf,",V_sqrt[j]);
			if(j==image_width){fprintf(fp_V_sqrt,"\n");}

			fprintf(fp_Cos_similarity,"%lf,",Cos_similarity[j]);
			if(j==image_width){fprintf(fp_Cos_similarity,"\n");}
			
			fprintf(fp_Angle,"%lf,",Angle[j]);
			if(j==image_width){fprintf(fp_Angle,"\n");}

			//fprintf(fp_Correction_flag,"%d,",Correction_flag[j]);
			//if(j==image_width){fprintf(fp_Correction_flag,"\n");}

			

			//fprintf(fp_newfunction,"%lf,",);									//出力増やす用6/7
			//if(j==image_width){fprintf(fp_newfunction,"\n");}


			


///////////////////////////書き込み終わり/////////////////////////////////////////////////////////			
			
			}																//閉じ　計算条件付近 "for(j=1;j<image_wide;++j){"
		}																	//閉じ　応答電圧のcsvの読み取り付近　"while(getline(V_0,str_0)){"
	//ファイルを閉じる
	fclose(fp_innerp);
	fclose(fp_V_sqrt);
	fclose(fp_Cos_similarity);
	fclose(fp_Angle);
	fclose(fp_threshold_high);
	fclose(fp_threshold2);
	fclose(fp_threshold);
	//fclose(fp_Correction_flag);
	//fclose(fp_newfunction);													//出力増やす用7/7 + log

////////////////////////logファイルの作成//////////////////////////////////////////////////////////////////////////
	FILE *fp_date;
	char filename_log[128];
	//sprintf(filename_log, "..\\log\\log-%2d-%02d%02d-%02d%02d%02d.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//logファイル作成のディレクトリ指定
	sprintf(filename_log, "..\\result_inu\\%2d-%02d%02d-%02d%02d%02d\\log.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);	//logファイル作成のディレクトリ指定
	if((fp_date=fopen(filename_log,"w"))==NULL){printf("logファイルが開けません");exit(1);}
	fprintf(fp_date,"Time       : %s",date);						//時間
	fprintf(fp_date,"direction  : %d\n",direction_number);			//方向
	fprintf(fp_date,"curcuit    : %d\n",curcuit_number);						//使用回路
	//fprintf(fp_date,"property   : %s\n",inputdate_directory1);				//propretyファイル
	fprintf(fp_date,"Rvector    : %d\n",Rvector_number);						//基準ベクトルの数
	fprintf(fp_date,"minor_flag : %d\n",minor_flag);							//マイナーナンバー
	fprintf(fp_date,"Rvector    : %s\n",inputrvector_directory);	//使用したRvectorデータ
	for(i=1;i<=8;i++){for(j=1;j<=8;j++){fprintf(fp_date,"%lf, ",Rvector[i][j]);}fprintf(fp_date,"\n");}	//使用したRvector
	fprintf(fp_date,"Rvector *	: %f,%f,%f,%f,%f,%f,%f,%f\n",Rvectormagni[1],Rvectormagni[2],Rvectormagni[3],Rvectormagni[4],Rvectormagni[5],Rvectormagni[6],Rvectormagni[7],Rvectormagni[8]);	//使用したRvectorの倍率
	fprintf(fp_date,"使用データ : %s\n",inputdate_directory);		//使用した畳み込み済みデータ
	fprintf(fp_date,"保存先     : %s\n",date_directory);			//保存先
	fclose(fp_date);

	printf("direction  : %d\n",direction_number);						//方向
	printf("curcuit	   : %d\n",curcuit_number);						//使用回路
	printf("Rvector	   : %d\n",Rvector_number);						//基準ベクトルの数
	printf("minor_flag : %d\n",minor_flag);							//マイナーナンバー
	printf("Rvector    : %s\n",inputrvector_directory);				//使用したRvectorデータ
	printf("使用データ : %s\n",inputdate_directory);				//使用した畳み込み済みデータ
	//printf("保存先     : %s\n",date_directory);						//保存先
	printf("logファイル %s を保存しました\n",filename_log);

	printf("%d回目処理完了\n",repeat);
	Sleep(1000);
	}																//閉じ"for(int repeat=0;repeat<6;++repeat)"
	
	return 0;
}
