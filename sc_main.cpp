//Alvi Ahmed 500696421
#include <systemc.h>
#include "CPA.h"
#include "CSA.h"
#define size 8
int sc_main(int argc, char* argv[]){ 
         int  truth_it = 8; 
         int i = 0; 
         int time = 9;
	 sc_trace_file *tf;                  // Create VCD file for tracing 

         sc_signal<sc_uint<size> > sum_cpa;  
         sc_signal<sc_uint<size> > carrout_cpa;
         sc_signal<sc_uint<size> > ain_cpa; 
         sc_signal<sc_uint<size> > bin_cpa;  
         sc_signal<sc_uint<size> > carrin_cpa;      
//***** added for 1 file trial
         sc_signal<sc_uint<size> > lsb_out_cpa;    
         sc_signal<sc_uint<size> > sum_out_csa;  
         sc_signal<sc_uint<size> > carry_out_csa;  
//***** added for 1 file trial
         sc_signal<sc_uint<size> > msb_out_cpa;   
         sc_signal<sc_uint<size> > lsb_in_cpa;  
         sc_signal<sc_uint<size*2> > com_byte; 

         sc_signal<sc_uint<size> > sum_csa;  
         sc_signal<sc_uint<size> > carrout_csa;
         sc_signal<sc_uint<size> > ain_csa; 
         sc_signal<sc_uint<size> > bin_csa;  
         sc_signal<sc_uint<size> > sin_csa;  
         sc_signal<sc_uint<size> > carrin_csa;    
         sc_signal<sc_uint<size> > lsb_out_csa;  
         
	 sc_clock clk("clk",10,SC_NS,0.5);   //Create a clock signal 

   	 CPA testing_CPA("CPA");            //Create Device Under Test (DUT) 

         //need to do module . .h variables
         testing_CPA.B_input(bin_cpa); 
         testing_CPA.A_input(ain_cpa);
         testing_CPA.carry_in(carrin_cpa);
         testing_CPA.carry_out(carrout_cpa);
         testing_CPA.sum_out(sum_cpa);   
//***** added for 1 file trial
         testing_CPA.lsb_out(lsb_out_cpa);  
         testing_CPA.sum_out_csa(sum_out_csa); 
         testing_CPA.carry_out_csa(carry_out_csa); 
         
//***** added for 1 file trial
         testing_CPA.msb_out(msb_out_cpa); 
         testing_CPA.complete(com_byte);  
         testing_CPA.least_sig(lsb_in_cpa); 

       // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file"); 

        tf->set_time_unit(1, SC_NS); 

	sc_trace(tf, msb_out_cpa, "MSB_output_cpa");    
	sc_trace(tf, com_byte, "Complete");    

//***** added for 1 file trial 
        sc_trace(tf, sum_out_csa, "Sum_CSA_output");
        sc_trace(tf, carry_out_csa, "Carry_CSA_output");  
        sc_trace(tf, bin_cpa, "B_input_whole_module");
        sc_trace(tf, ain_cpa, "A_input_whole_module");  
//***** added for 1 file trial 


//***** added for 1 file trial 
        sc_trace(tf, lsb_out_cpa, "LSB_output_cpa");
//***** added for 1 file trial 

	cout << "\nExecuting CPA example... check .vcd produced"<<endl;
	//start the testbench   

        ain_cpa.write(3);    //actual output of 1 CPA test case
        bin_cpa.write(2);   //      
	sc_start(20, SC_NS);    

        ain_cpa.write(30);    //actual output of 1 CPA test case
        bin_cpa.write(20);   //      
	sc_start(20, SC_NS);   

        ain_cpa.write(5);    //actual output of 1 CPA test case
        bin_cpa.write(5);   //      
	sc_start(20, SC_NS);   

        ain_cpa.write(100);    //actual output of 1 CPA test case
        bin_cpa.write(200);   //      
	sc_start(20, SC_NS);     

        ain_cpa.write(255);    //actual output of 1 CPA test case
        bin_cpa.write(255);   //      
	sc_start(20, SC_NS);    

        ain_cpa.write(60);    //actual output of 1 CPA test case
        bin_cpa.write(70);   //      
	sc_start(20, SC_NS);    
   	sc_close_vcd_trace_file(tf);
   	
   	return 0;                         
}
