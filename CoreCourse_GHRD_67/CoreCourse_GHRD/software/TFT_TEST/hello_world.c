/*
 * "Hello TFT" example.
 * v1.0.0:С÷��-20160723
 * ����������������������������������������������������������������������������������������������������
 * |�������̣�ʵ��ͼ����Ӣ������ʾ��
 *
 * v1.0.1:��������-20160724
 * ������������������������������������������������������������������������������������������������������
 * |�޸�suggest parentheses around '+' inside '<<' [-Wparentheses]���档
 * |����LCD_printf���������л������ԡ�
 *
 */

#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "io.h"
//#include "welcom.h"
#include "unistd.h"
#include "TFT_API.h"
#include "font_chinese.h"
#include "altera_avalon_uart_regs.h"
#include "liuyifei1.h"

char rx_data[256];
char tx_data[256];
char rx_data_offset;
char tx_data_offset;
char len_to_tx;
char data_tx[10] =
		{ 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0xaa, 0x55 };

//ʹ�ò�ѯ��ʽ���Ե������ڵ����ݽ����շ�
void uart_rx_tx(unsigned int UART_BASE)
{

	unsigned int uart_state;
	uart_state = IORD_ALTERA_AVALON_UART_STATUS(UART_BASE);//��ȡ����״̬
	if(uart_state & ALTERA_AVALON_UART_CONTROL_RRDY_MSK)	//���ճɹ�
	{
	  //�����յ������ݴ洢������������
	  rx_data[rx_data_offset] = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
	  //���ݴ洢ָ��+1
	  rx_data_offset ++;
	}

	if((uart_state & ALTERA_AVALON_UART_CONTROL_TRDY_MSK) && len_to_tx)//���ͼĴ���Ϊ�գ��ɷ���������
	{
	  IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE,tx_data[tx_data_offset]);
	  tx_data_offset ++;
	  len_to_tx --;
	  if(!len_to_tx)//�������
		  tx_data_offset = 0;	//��λ�������ݵ�ַָ��
	}
}


int main() {
	int i;
	//printf("Hello from Nios II!\n");

	IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, UART_0_FREQ/115200 - 1);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xff);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd8);

	for (i = 0; i < 640 * 480 * 2; i++) {
		while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
				& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
			;
		IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, gImage_liuyifei[i]);
	}

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd9);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd9);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd9);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd9);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xff);

	while (!(ALTERA_AVALON_UART_STATUS_TRDY_MSK
			& IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)))
		;
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 0xd9);
//  for (i=0;i<10;i++)
//  {
//	  while(!(ALTERA_AVALON_UART_STATUS_TRDY_MSK & IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE)));
//	   	  IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, data_tx[i]);
//  }
//
//  alt_u32 i,j,n;
//  alt_u8 k=6;
//
//  for(i=0;i<480*272;i++)
//	  TFT_WR(i, ~0xffff);
//
//  TFT_WR(0, 0xffff);
//  TFT_WR(479, 0xffff);
//  TFT_WR(480*271, 0xffff);
//  TFT_WR(480*272 - 1, 0xffff);
//
//  for(i=100;i<200;i++)
//	  for(j=50;j<150;j++)
//		  TFT_WR_XY(j,i,0xf000);
//
//  n = 0;
//
//  for (i = 0; i < 272; i++) {
//		for (j = 0; j < 480; j++) {
//			TFT_WR_XY(j, i, (welcom[n]<<8) + welcom[n+1]);
//			n = n + 2;
//		}
//	}
//
//  LCD_Dir(LCD_HORIZONTAL);
//
//  LCD_ShowString(360,20,16,"hello");
//  for(i=0;i<100;i++)
//  {
//	  LCD_printf(&lcd_printf, "String Len is: %d\n", (alt_u8)i);
//	  usleep(100000);
//  }

	while (1)
		;

	return 0;
}