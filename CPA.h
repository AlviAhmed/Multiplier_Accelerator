#ifndef CPA_H   //it is a guard feature, included in to prevent double declaration, this is in your C++ book you used to study
#define CPA_H
#include <systemc.h>        
#include "CSA.h"
#define size 8
SC_MODULE(CPA) { //some random names you can give I guess
	sc_in<sc_uint<size> > B_input;
	sc_in<sc_uint<size> > A_input;
	sc_in<sc_uint<size> > carry_in;   
	sc_in<sc_uint<size> > least_sig;  
	sc_out<sc_uint<size> > carry_out; 
	sc_out<sc_uint<size> > sum_out;    
//***** added for 1 file trial
	sc_out<sc_uint<size> > lsb_out;   
	sc_out<sc_uint<size> > sum_out_csa;    
	sc_out<sc_uint<size> > carry_out_csa;    
//***** added for 1 file trial
	sc_out<sc_uint<size> > msb_out;  
	sc_out<sc_uint<size*2> > complete;  
	void CPA_method();     
        SC_CTOR(CPA) { 
        SC_METHOD(CPA_method);
	dont_initialize();
        sensitive << A_input << B_input << carry_in; //edge sensitive (positive)
    }
}; 

#endif 
