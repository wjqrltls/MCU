void Init_ADC()
{
	//- ADC1 ä��, AREF ���� ����
	ADMUX = 1;
	//- ä��, Ȱ��ȭ, ���������� ����
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}