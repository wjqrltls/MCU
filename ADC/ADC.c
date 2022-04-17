void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압
	ADMUX = 1;
	//- 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}