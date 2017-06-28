/*
 *  utilities.cpp
 *  updated on June 27, 2017
 *  updated by Zheng Xing <zxing@robohome.org>
 *  
 */


class IncrementingIntegerGenerator {
public:
	IncrementingIntegerGenerator() :
			i_(1) {}
	int operator()() {
		return i_++;
	}
private:
	int i_;
} incrementing_integer;