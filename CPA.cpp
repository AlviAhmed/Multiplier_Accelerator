//Alvi Ahmed 500696421 
#include "CPA.h"    
#include "CSA.h" 

#define size 8 
//*************************************** CSA Definition
sc_uint<size > sum;  
sc_uint<size > carrout;
sc_uint<size > ain; 
sc_uint<size > bin;    
sc_uint<size > A_combined;   
sc_uint<size > sin_input;   
sc_uint<size > ainandbin; 
sc_uint<size > lsb_val;
sc_uint<size > carrin;     
sc_uint<size > sum_actual; 
sc_uint<size > carr_actual; 
sc_uint<size > sum_simplier; 
sc_uint<size > carr_simplier;
int i = 0; 
int j = 0;     
int y = 0;
int sum_holder[size][size];
int carrout_holder[size][size];
//*************************************** CSA Definition


// ******************************* CPA definition
sc_uint<size> sum_cpa;  
sc_uint<size> carrout_cpa;   

sc_uint<size> sum_holder_cpa;  
sc_uint<size> carrout_holder_cpa;  

sc_uint<size> sum_csa;  

sc_uint<size> carrout_csa;
sc_uint<size> ain_cpa; 
sc_uint<size> bin_cpa;   
sc_uint<size> carrin_cpa;      

sc_uint<size> least_significant;      
sc_uint<size*2> complete_output; 

sc_uint<size > msb_val;
int x, w = 0;
int z = 0;  
// ******************************* CPA definition


// a xor b  
// b and c 
// (a xor b)  xor cin  => sum  -> main eq
// (a and c) OR (a and b) => cout -> main eq 

 void CPA :: CPA_method() {     
	cout << endl;   

//**************************************** CSA Method
        	ain = A_input.read();  
        	bin = B_input.read();        
                A_combined = ain & bin;
       		for (i = 0; i < size; i ++ ){ //row number   

                  for (j = 0 ; j < size; j ++){ //column number     
                    if (i == 0){   //if first row , C = 0 and S = 0
                      sin_input = 0; 
                      carrin = 0;    
                      
                      A_combined = ain[j] & bin[i];
                      sum = (( (A_combined) ^ (sin_input)) ^ (carrin));   //((axorb)) xor cin 
                      carrout = ((A_combined) & sin_input)  | (sin_input & carrin) | (A_combined & carrin);   
                      if (j == 0){  
                        lsb_val[i] = sum[j]; //every row that last column sum will be stored in the lsb register
                      } 
                      sum_holder[i][j] = sum; //holder current coloum number (i.e first coloum A3) 
                      carrout_holder[i][j] = carrout; //holder current coloum number (i.e first coloum A3)       
                    }   
                    
                    else if (j == (size - 1) && (i != 0)){  //S = 0  

                      A_combined = ain[j] & bin[i];
                      carrin = carrout_holder[i - 1][j];  //will have to make equal carrout value in same coloum but previous row  
                      sin_input = 0;
                      sum = (( (A_combined) ^ (sin_input)) ^ (carrin));   //((axorb)) xor cin 
                      carrout = ((A_combined) & sin_input)  | (sin_input & carrin) | (A_combined & carrin); 
                      
                      sum_holder[i][j] = sum; //holder current coloum number (i.e first coloum A3) 
                      carrout_holder[i][j] = carrout; //holder current coloum number (i.e first coloum A3)        
                      
                    }   

                    else{  

                      A_combined = ain[j] & bin[i];
                      carrin = carrout_holder[i - 1][j];  //will have to make equal carrout value in same coloum but previous row 
                      sin_input = sum_holder[i-1][j+1]; //will have to make sin input the previous row & future columb 
                      sum = (( (A_combined) ^ (sin_input)) ^ (carrin));   //((axorb)) xor cin 
                      carrout = ((A_combined) & sin_input)  | (sin_input & carrin) | (A_combined & carrin); 
                      
                      sum_holder[i][j] = sum; //holder current coloum number (i.e first coloum A3) 
                      carrout_holder[i][j] = carrout; //holder current coloum number (i.e first coloum A3)        

                      if (j == 0){  
                        lsb_val[i] = sum[j]; //every row that last column sum will be stored in the lsb register
                      }  
                      
                    }       

                  } 
		}     

                for (y = 0; y < size; y++){  //column
                  sum_simplier[y] = sum_holder[size-1][y];
                  carr_simplier[y] = carrout_holder[size-1][y];
                } 

                lsb_out.write(lsb_val); 
                carry_out_csa.write(carr_simplier); 
                sum_out_csa.write(sum_simplier);      

//**************************************** CSA Method

                sum_csa = sum_simplier; 
                carrout_csa = carr_simplier; 
                least_significant = lsb_val;
        	//sum_csa = A_input.read();  //in sc_main sum_csa will be inputted into CPA A_input
        	//carrout_csa = B_input.read();  //in sc_main sum_csa will be inputted into CPA B_input  
                //least_significant = least_sig.read();


                for (x = 0; x < size; x ++){    //x is column #
                    if (x == 0){  //if A0
                      carrin_cpa = 0; 
                      ain_cpa = sum_csa[x+1];  
                      bin_cpa = carrout_csa[x];   

                      sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carrin_cpa));  
                      carrout_cpa = ((ain_cpa & bin_cpa) | (carrin_cpa & bin_cpa) | (ain_cpa & carrin_cpa));    
                      
                      sum_holder_cpa[x] = sum_cpa;   
                      msb_val[x] = sum_cpa; 
                      carrout_holder_cpa[x] = carrout_cpa;  
                      
                    }  

                    else if (x == (size - 1)){ //if x = A3 
                      carrin_cpa = 0; 
                      bin_cpa = carrout_holder_cpa[x-1]; 
                      ain_cpa = carrout_csa[x];  

                      sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carrin_cpa));  
                      carrout_cpa = ((ain_cpa & bin_cpa) | (carrin_cpa & bin_cpa) | (ain_cpa & carrin_cpa));    
                      
                      sum_holder_cpa[x] = sum_cpa;   
                      msb_val[x] = sum_cpa; 
                      carrout_holder_cpa[x] = carrout_cpa;   


                    } 
                    else{ 
                      carrin_cpa = carrout_holder_cpa[x-1]; //making C in equal to prev value C out 
                      bin_cpa = carrout_csa[x]; 
                      ain_cpa = sum_csa[x+1];  

                      sum_cpa = ((ain_cpa ^ bin_cpa) ^ (carrin_cpa));  
                      carrout_cpa = ((ain_cpa & bin_cpa) | (carrin_cpa & bin_cpa) | (ain_cpa & carrin_cpa));    
                      
                      sum_holder_cpa[x] = sum_cpa;   
                      msb_val[x] = sum_cpa; 
                      carrout_holder_cpa[x] = carrout_cpa;  
                      

                    }  
                    cout << sum_holder_cpa[x];
                }    

                msb_out.write(msb_val); 
 //              cout << " Here is the MSB: " << endl;
//               for (x = 0; x < size; x ++){  
//                 cout << msb_val[x];
//               }  
//               cout << endl;    

               for (z = 0; z < (size*2); z ++){ 
                 if (z < (size)){ 
                   complete_output[z] =  least_significant[z]; 
                 }  
                 else { 
                   complete_output[z] =  msb_val[z - size]; 
                 }
               } 

               complete.write(complete_output);
                
 }
