#pragma warning(disable : 4996)
#include<stdio.h>
#include <stdlib.h>
#include<windows.h>
int *message ;
int calculation_Checksum(int *message, int i) {
	unsigned int sum = 0;
	int j = 0;
	unsigned int left, right, Wsum = 0;
	unsigned short Checksum=0;

	

	while (j<=i-1) { // 메세지의 숫자들 더하기
		sum += message[j];
		j++;
	}
	left = sum >> 16;	//32비트 중 좌측 16비트 수
	right = sum & 0xffff;	//32비트 중 우측 16비트 수
	

	while (left != 0) {	// 좌측 비트가 없을 때 까지
		Wsum = left + right;
		left = Wsum >> 16;
		right = Wsum & 0xffff;
	}
	Wsum = right; //Wrapped sum 값
	Checksum = (~Wsum); //Wrapped sum 값을 보수화 하여 Checksum에 저장 checksum 이 2byte의 값이므로 trancate 된다.
	message[i] = Checksum; //Checksum 값을 메세지에 붙여 전달
	return Checksum;
}
int check_Checksum(int *message, int i){
	unsigned int sum = 0;
	int j = 0;
	unsigned int left, right, Wsum = 0;
	unsigned short Checksum;
	
	while (j <= i+1) { // 메세지의 숫자들 더하기
		sum += message[j];
		j++;
	}
	left = sum >> 16;	//32비트 중 좌측 16비트 수
	right = sum & 0xffff;	//32비트 중 우측 16비트 수

	while (left != 0) {	// 좌측 비트가 없을 때 까지
		Wsum = left + right;
		left = Wsum >> 16;
		right = Wsum & 0xffff;
	}
	Wsum = right; //Wrapped sum 값
	Checksum = ~Wsum; //Wrapped sum 값을 보수화 하여 Checksum에 저장

	if(Checksum ==0){ //Checksum 값으로 오류 검출
		return 1;
	}
	else {
		return 0;
	}
}


int main() {
	int i = 0;
	unsigned int a;
	int j = 0;

	//message 갯수 정하기
	printf("메세지의 갯수를 정해주세요 \n");
	scanf("%d", &j);

	//message 동적할당
	message = (int*)malloc(sizeof(int) * j);
	if (message == NULL) {
		return 0;
	}

	//message 받기
	for(i=0;i<j;i++){
		printf("message[%d] : ",i);
		scanf("%d",&a);
		message[i] = a;
	}
	
	printf("발신 측 Checksum 값 : %d\n", calculation_Checksum(message, i));
	printf("수신중...\n");
	Sleep(1000);
	printf("수신 측 검사중...\n");
	Sleep(1000);
	if (check_Checksum(message, i) == 1) {
		printf("오류가 발생했습니다!!!\n");
	}
	else if (check_Checksum(message, i) == 0){
		printf("정상적으로 전달되었습니다\n");
	}

	
}
