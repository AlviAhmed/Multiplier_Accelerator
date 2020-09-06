#ifndef CSA_H   //it is a guard feature, included in to prevent double declaration, this is in your C++ book you used to study
#define CSA_H
#include <systemc.h>       
#define size 8
SC_MODULE(CSA) { //some random names you can give I guess
	sc_in<sc_uint<size> > B_input;
	sc_in<sc_uint<size> > A_input; 
	sc_in<sc_uint<size> > S_input;
	sc_in<sc_uint<size> > carry_in;  
	sc_out<sc_uint<size > > carry_out; 
	sc_out<sc_uint<size > > sum_out;  
        sc_out<sc_uint<size> > lsb_out;
	void CSA_method();     
        SC_CTOR(CSA) { 
 SC_METHOD(CSA_method);
	dont_initialize();
        sensitive << A_input << B_input << S_input << carry_in; //edge sensitive (positive)
    }
}; 

#endif 
