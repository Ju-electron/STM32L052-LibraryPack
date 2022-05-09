/*
 * SK6812.c
 *
 *  Created on: Mar 23, 2022
 *      Author: js372
 *
 *      [Notice]
 *      This Library using SPI and DMA.
 *
 *      CPU Clock: 24MHz
 *      SPI Clock Prescaler: 8
 *      Please type "HAL_DMA_Init(&hdma_spi1_tx);" in User code2 Area
 */
#include <sk6812.h>

extern SPI_HandleTypeDef hspi1;

uint32_t spiBf[109];
uint32_t ledData[36][3];
const uint32_t colLUT[]={
		2290649224, 2357758088, 3364391048, 3431499912, 2290911368, 2358020232, 3364653192, 3431762056,
		2294843528, 2361952392, 3368585352, 3435694216, 2295105672, 2362214536, 3368847496, 3435956360,
		2290650248, 2357759112, 3364392072, 3431500936, 2290912392, 2358021256, 3364654216, 3431763080,
		2294844552, 2361953416, 3368586376, 3435695240, 2295106696, 2362215560, 3368848520, 3435957384,
		2290665608, 2357774472, 3364407432, 3431516296, 2290927752, 2358036616, 3364669576, 3431778440,
		2294859912, 2361968776, 3368601736, 3435710600, 2295122056, 2362230920, 3368863880, 3435972744,
		2290666632, 2357775496, 3364408456, 3431517320, 2290928776, 2358037640, 3364670600, 3431779464,
		2294860936, 2361969800, 3368602760, 3435711624, 2295123080, 2362231944, 3368864904, 3435973768,
		2290649228, 2357758092, 3364391052, 3431499916, 2290911372, 2358020236, 3364653196, 3431762060,
		2294843532, 2361952396, 3368585356, 3435694220, 2295105676, 2362214540, 3368847500, 3435956364,
		2290650252, 2357759116, 3364392076, 3431500940, 2290912396, 2358021260, 3364654220, 3431763084,
		2294844556, 2361953420, 3368586380, 3435695244, 2295106700, 2362215564, 3368848524, 3435957388,
		2290665612, 2357774476, 3364407436, 3431516300, 2290927756, 2358036620, 3364669580, 3431778444,
		2294859916, 2361968780, 3368601740, 3435710604, 2295122060, 2362230924, 3368863884, 3435972748,
		2290666636, 2357775500, 3364408460, 3431517324, 2290928780, 2358037644, 3364670604, 3431779468,
		2294860940, 2361969804, 3368602764, 3435711628, 2295123084, 2362231948, 3368864908, 3435973772,
		2290649288, 2357758152, 3364391112, 3431499976, 2290911432, 2358020296, 3364653256, 3431762120,
		2294843592, 2361952456, 3368585416, 3435694280, 2295105736, 2362214600, 3368847560, 3435956424,
		2290650312, 2357759176, 3364392136, 3431501000, 2290912456, 2358021320, 3364654280, 3431763144,
		2294844616, 2361953480, 3368586440, 3435695304, 2295106760, 2362215624, 3368848584, 3435957448,
		2290665672, 2357774536, 3364407496, 3431516360, 2290927816, 2358036680, 3364669640, 3431778504,
		2294859976, 2361968840, 3368601800, 3435710664, 2295122120, 2362230984, 3368863944, 3435972808,
		2290666696, 2357775560, 3364408520, 3431517384, 2290928840, 2358037704, 3364670664, 3431779528,
		2294861000, 2361969864, 3368602824, 3435711688, 2295123144, 2362232008, 3368864968, 3435973832,
		2290649292, 2357758156, 3364391116, 3431499980, 2290911436, 2358020300, 3364653260, 3431762124,
		2294843596, 2361952460, 3368585420, 3435694284, 2295105740, 2362214604, 3368847564, 3435956428,
		2290650316, 2357759180, 3364392140, 3431501004, 2290912460, 2358021324, 3364654284, 3431763148,
		2294844620, 2361953484, 3368586444, 3435695308, 2295106764, 2362215628, 3368848588, 3435957452,
		2290665676, 2357774540, 3364407500, 3431516364, 2290927820, 2358036684, 3364669644, 3431778508,
		2294859980, 2361968844, 3368601804, 3435710668, 2295122124, 2362230988, 3368863948, 3435972812,
		2290666700, 2357775564, 3364408524, 3431517388, 2290928844, 2358037708, 3364670668, 3431779532,
		2294861004, 2361969868, 3368602828, 3435711692, 2295123148, 2362232012, 3368864972, 3435973836
};
void led_color(uint8_t id, uint8_t r, uint8_t g, uint8_t b){
	ledData[id][0]=g;
	ledData[id][1]=r;
	ledData[id][2]=b;
}
void led_update(){
	for(int i=0; i<36; i++){
		spiBf[(i*3)]=colLUT[ledData[i][0]];
		spiBf[(i*3)+1]=colLUT[ledData[i][1]];
		spiBf[(i*3)+2]=colLUT[ledData[i][2]];
	}
	spiBf[108]=0;
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)spiBf, 436);
}
void led_clear(){
	memset(ledData,0,sizeof(ledData));
	led_update();
}
