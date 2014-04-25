//Author Paola Giannetti, Marco Piendibene
//
//Version 1.0
//Date 22-04-2006
//
// revision 1.1; Commentate alcune parti per permettere di simulare il resto. (mp 27.06.07)
// revision 2.0 Marco Piendibene, settembre 2007.
// rev MP 18.10.2007
// rev VB 26.07.10
// ripristinata la compatibilita' con edro dovuta a mismatch serdes
// Revision  Daniel Magalotti e Marco Piendibene, aprile 2011
`timescale 1ns/1ps
//`timescale 1 ns / 100 ps		 
module AM_ctrl(	
            clk,						// (I) System clock, 40 Mhz
						init,						// (O) Reset genrato a partire da back_init e da vme

// **** VME PORTS ****

						vme_data,			// (IO) VME data bus (32 bits)

						vadd,						// (I) Valid Address bits (identifies the internal chip of the board)

						am,						// (I) Address mode signal

						geadd,					// (I) geographical address

						as_b,						// (I) address strobe

						ds0_b,						// (I) data strobe		
						ds1_b,						// (I) data strobe		

						berr_b,					// (O) Bus error signal. Asserted when address is wrong

						iack_b,					// (I) Interrupt aknowledge

						lword_b,					// (I) Long word signal

						write_b,					// (I) States the direction of data flow

						dtack_b,					// (O) Data aknowledge signal

// From/To Hit FIFOs

						lay0_in,				      // (I) Input from the Hit Fifo
						lay1_in,				      // (I) Input from the Hit Fifo
						lay2_in,				      // (I) Input from the Hit Fifo
						lay3_in,				      // (I) Input from the Hit Fifo
						lay4_in,				      // (I) Input from the Hit Fifo
						lay5_in,				      // (I) Input from the Hit Fifo
						
						ef_b,						      // (I) Hit fifos empty flags
						rden_b,					      // (O) Hit fifos read enables

						resfifo0_b,				   // (O) Hit fifos reset
						resfifo1_b,				   // (O) Hit fifos reset
									

// From/To LAMB_A

						A0_HIT,					      // (O) Bus for lamb A
						A1_HIT,					      // (O) Bus for lamb A
						A2_HIT,					      // (O) Bus for lamb A
						A3_HIT,					      // (O) Bus for lamb A
						A4_HIT,					      // (O) Bus for lamb A
						A5_HIT, 				      // (O) Bus for lamb A
						enA_wr,					      // (O) Enable for the 6 buses at each of 4 lambs
						init_ev0_lamb0, 		// (O) Lamb0 init. From main FSM
						init_ev1_lamb0, 		// (O) Lamb0 init. From main FSM
						init_ev2_lamb0, 		// (O) Lamb0 init. From main FSM
						sel0_b,					      // (O) data acknowledge for lamb0
						opcode0_out,			   // (O) OPCODE lamb0
						dr0_b,						      // (I) Valid data from lamb0
						ladd0,					       // (I) data (road) form lamb0
						tck_am_lamb0,			  // (O) tck signal to LAMB0 board

// From/To LAMB_B

						B0_HIT,					      // (O) Bus for lamb B
						B1_HIT,					      // (O) Bus for lamb B
						B2_HIT,					      // (O) Bus for lamb B
						B3_HIT,					      // (O) Bus for lamb B
						B4_HIT,				       // (O) Bus for lamb B // non lo usiamo questo bus (commented)
						B5_HIT,					      // (O) Bus for lamb B
						enB_wr,					      // (O) Enable for the 6 buses at each of 4 lambs
						init_ev0_lamb1, 		// (O) Lamb1 init. From main FSM
						init_ev1_lamb1, 		// (O) Lamb1 init. From main FSM
						init_ev2_lamb1, 		// (O) Lamb1 init. From main FSM
						sel1_b,					      // (O) data acknowledge for lamb1
						opcode1_out,			   // (O) OPCODE lamb1
						dr1_b,						      // (I) Valid data from lamb1
						ladd1,					       // (I) data (road) form lamb1
						tck_am_lamb1,			  // (O) tck signal to LAMB1 board

// From/To LAMB_C

						C0_HIT,					      // (O) Bus for lamb C
						C1_HIT,					      // (O) Bus for lamb C
						C2_HIT,					      // (O) Bus for lamb C
						C3_HIT,					      // (O) Bus for lamb C
						C4_HIT,					      // (O) Bus for lamb C
						C5_HIT,					      // (O) Bus for lamb C
						enC_wr,					      // (O) Enable for the 6 buses at each of 4 lambs
						init_ev0_lamb2, 		// (O) Lamb2 init. From main FSM
						init_ev1_lamb2, 		// (O) Lamb2 init. From main FSM
						init_ev2_lamb2, 		// (O) Lamb2 init. From main FSM
						sel2_b,					      // (O) data acknowledge for lamb2
						opcode2_out,			   // (O) OPCODE lamb2
						dr2_b,						      // (I) Valid data from lamb2
						ladd2,					       // (I) data (road) form lamb2
						tck_am_lamb2,			  // (O) tck signal to LAMB2 board

// From/To LAMB_D

						D0_HIT,					      // (O) Bus for lamb D
						D1_HIT,					      // (O) Bus for lamb D
						D2_HIT,					      // (O) Bus for lamb D 
						D3_HIT,					      // (O) Bus for lamb D
						D4_HIT,				       // (O) Bus for lamb D  // non lo usiamo questo bus (commented)
						D5_HIT,					      // (O) Bus for lamb D
						enD_wr,					      // (O) Enable for the 6 buses at each of 4 lambs
						init_ev0_lamb3, 		// (O) Lamb3 init. From main FSM
						init_ev1_lamb3, 		// (O) Lamb3 init. From main FSM
						init_ev2_lamb3, 		// (O) Lamb3 init. From main FSM
						sel3_b,   				    // (O) data acknowledge for lamb3
						opcode3_out,			   // (O) OPCODE lamb3
						dr3_b,						      // (I) Valid data from lamb3
						ladd3,					       // (I) data (road) form lamb3
						tck_am_lamb3,			  // (O) tck signal to LAMB3 board
						
// Other signals

						odata,					// (O) Roads (only from lamb in SLIM)
						wr_road,					// (O) Data valid for the roads
						push,						// (O) sends the hit to P3 output. Only for debug in SLIM (?????????)
						bitmap_status,			// (O) indicates road or road+bitmap at lambs
						wrpam,					// (O) write enable signal on PAM register via TDI
						rdbscan,					// (O) read enable of the output of boundary scan chip
						enb_b,						// (O) Data flow direction on the bscan registers
						dirw_b,					// (O) Data flow direction on the bscan registers
						add,						// (O) VME address subset sent to bscan chip on lamb
						lamb_spare,    		// 
						road_end,      		//
						rhold_b,					// (I) Hold delle fifo delle schede a valle. Noi non li abbiamo ????????
						backhold_b,				// (I)  (?????????????????????????????????????????)
						en_back,					// (I) Enable road output on P2 (for debug)
					  back_init				// (I) Init From P2 (backplane init)
						
						
						//init_iam0,			// al posto loro generare 12 segnali di reset (3 per lamb)
						//init_iam1,			// al posto loro generare 12 segnali di reset (3 per lamb)
						
						
						
						
						//roadend0_in,			// (I) dalle lamb: sostituiti da una parola di end_event
						//roadend1_in,			// (I) dalle lamb: sostituiti da una parola di end_event
						//roadend2_in,			// (I) dalle lamb: sostituiti da una parola di end_event
						//roadend3_in,			// (I) dalle lamb: sostituiti da una parola di end_event
			);





////////////////////////
//// I N P U T /////////
////////////////////////
input  clk;
input  dr0_b, dr1_b, dr2_b, dr3_b;
input  [20:0] ladd0, ladd1,ladd2, ladd3;
input  [3:0] lamb_spare;
input  [3:0] road_end;
input  rhold_b;
input  backhold_b;
input  en_back;   	//(?????????????????????) NOT USED
input  [20:0] lay0_in, lay1_in, lay2_in;
input  [20:0] lay3_in, lay4_in, lay5_in;
inout  [31:0] vme_data;
input  back_init;					// Init From P2 (backplane init)
input  [4:0]geadd;				// geographical address
input  as_b;							// address strobe
input  ds0_b;						// data strobe		
input  ds1_b;						// data strobe		
input  [5:0]am;					// Address mode signal
input  lword_b;						// Long word signal
input  iack_b;						// Interrupt aknowledge
input  write_b;						// States the direction of data flow
input  [31:1]vadd;				// Valid Address bits (identifies the internal chip of the board)
input [5:0] ef_b;


////////////////////////
//// O U T P U T ///////
////////////////////////
output init;
output [5:0] push;
output [3:0] bitmap_status;
output sel0_b, sel1_b, sel2_b, sel3_b;
output [3:0] opcode0_out, opcode1_out, opcode2_out, opcode3_out;
output init_ev0_lamb0, init_ev1_lamb0, init_ev2_lamb0;
output init_ev0_lamb1, init_ev1_lamb1, init_ev2_lamb1;  
output init_ev0_lamb2, init_ev1_lamb2, init_ev2_lamb2;  
output init_ev0_lamb3, init_ev1_lamb3, init_ev2_lamb3;
output wrpam;							// write enable signal on PAM register via TDI
output rdbscan;						// read enable of the output of boundary scan chip
output berr_b;							// Bus error singnal. Asserted when address is wrong
output dtack_b;							// Data aknowledge signal
output enb_b;							// Data flow direction on the bscan registers
output dirw_b;							// Data flow direction on the bscan registers
output [2:0]add;						// VME address subset sent to bscan chip on lamb	
output tck_am_lamb0;					// tck signal to LAMB 0 board
output tck_am_lamb1;					// tck signal to LAMB 0 board
output tck_am_lamb2;					// tck signal to LAMB 0 board
output tck_am_lamb3;					// tck signal to LAMB 0 board
output [17:0] A0_HIT, A1_HIT, A2_HIT;			// 6 buses for LAMB A
output [17:0] A3_HIT, A4_HIT, A5_HIT;			
output [17:0] B0_HIT, B1_HIT, B2_HIT; 			// 6 buses for LAMB B
output [17:0] B3_HIT, B4_HIT, B5_HIT; 	//  B4_HIT non lo usiamo
output [17:0] C0_HIT, C1_HIT, C2_HIT; 			// 6 buses for LAMB C
output [17:0] C3_HIT, C4_HIT, C5_HIT; 
output [17:0] D0_HIT, D1_HIT, D2_HIT; 			// 6 buses for LAMB D
output [17:0] D3_HIT, D4_HIT, D5_HIT; 		//  D4_HIT non lo usiamo
output [5:0] enA_wr, enB_wr, enC_wr, enD_wr;		// enables for 6 buses at each of 4 Lambs
output [29:0] odata;      								 // dati in uscita dalla scheda
output [5:0] rden_b;
output resfifo0_b, resfifo1_b;
output wr_road;             	 // data strobe_ per la fifo della scheda successiva



//////////////////////////////
//// W I R E AND R E G ///////
//////////////////////////////
// inverto il layer0 perche' e' sbagliato il routing sulla scheda
wire [20:0] lay0_in_neg = ~lay0_in;
wire clk;
wire init;
wire rpush;
wire [3:0] road_end;
wire [22:0] ladd;
wire sel_loc_road, dr_;
wire [29:0] odata_tmp;		// odata
wire wr_road;
wire init_ev;
wire [19:0] ivdata_input;
wire [31:0] ivdata_vme;
wire [26:2] ivadd;		// internal vme addr. From vme module
wire rd_input, wr_input;
wire rd_vme;
//wire [7:0] debug_am_glue;
wire [1:0] input_ctr_debug;
wire [5:0] hee_reg;
wire [2:0] state;					// per debug li andiamo a rileggere via vme
wire [5:0] en;		
wire [2:0] rwadd;
wire [17:0]hitmask;		// Maschera per gli hit che vanno alle lambs
wire [17:0]xxx_hitmask = 18'b0;		// Maschera per gli hit che vanno alle lambs
wire int_clk;
wire [5:0] reg_en, pok, pop;	
wire [15:0] curr_tag;
wire logic_0 = 1'b0;
//wire logic1 = 1'b1;


wire [31:0] count_patt;
wire [31:0] count_event;
wire [19:0] vme_input0_fifo;
wire [19:0] vme_input1_fifo;
wire [19:0] vme_input2_fifo;
wire [19:0] vme_input3_fifo;
wire [19:0] vme_input4_fifo;
wire [19:0] vme_input5_fifo;

wire [20:0] data_ispy0;
wire [20:0] data_ispy1;
wire [20:0] data_ispy2;
wire [20:0] data_ispy3;
wire [20:0] data_ispy4;
wire [20:0] data_ispy5;

wire [17:0] HIT_lay0;
wire [17:0] HIT_lay1;
wire [17:0] HIT_lay2;
wire [17:0] HIT_lay3;
wire [17:0] HIT_lay4;
wire [17:0] HIT_lay5;

wire [5:0] push_data_ispy;
wire [5:0] wr_fifo;
wire [5:0] push;

//wire [8:0] vme_block;
wire [14:0] vme_block;
reg [31:0] ivdata;


// SPYBUFFERS signals
wire freeze;

wire [29:0] ospy_data_out;
wire ospy_sel;
wire ospy_of;
wire [9:0] ospy_addr;
wire [11:0] ospy_status = {freeze, ospy_of, ospy_addr};	

wire [20:0] ispy0_data_out;
wire ispy0_sel;
wire ispy0_of;
wire [9:0] ispy0_addr;
wire [11:0] ispy0_status = {freeze, ispy0_of, ispy0_addr};	

wire [20:0] ispy1_data_out;
wire ispy1_sel;
wire ispy1_of;
wire [9:0] ispy1_addr;
wire [11:0] ispy1_status = {freeze, ispy1_of, ispy1_addr};	

wire [20:0] ispy2_data_out;
wire ispy2_sel;
wire ispy2_of;
wire [9:0] ispy2_addr;
wire [11:0] ispy2_status = {freeze, ispy2_of, ispy2_addr};	

wire [20:0] ispy3_data_out;
wire ispy3_sel;
wire ispy3_of;
wire [9:0] ispy3_addr;
wire [11:0] ispy3_status = {freeze, ispy3_of, ispy3_addr};	

wire [20:0] ispy4_data_out;
wire ispy4_sel;
wire ispy4_of;
wire [9:0] ispy4_addr;
wire [11:0] ispy4_status = {freeze, ispy4_of, ispy4_addr};	

wire [20:0] ispy5_data_out;
wire ispy5_sel;
wire ispy5_of;
wire [9:0] ispy5_addr;
wire [11:0] ispy5_status = {freeze, ispy5_of, ispy5_addr};	
// end spybuffers signals -------------------

wire xxx_init;

assign init = back_init;

`define rd_total {rd_vme, rd_input }
always @ (rd_vme or rd_input or ivdata_vme or ivdata_input)
case (`rd_total)
	2'b01: ivdata = {12'b0, ivdata_input}; 
  2'b10: ivdata = ivdata_vme; 
	default: ivdata = 32'b0;
endcase 

assign vme_data[31:0] = (rd_vme || rd_input)? ivdata[31:0] : 32'bz;

// output bologna 31.07.08 per usare ambslim con u n solo serializzatore sulle roads (mp 31.07.08)
// assign odata[0] = odata_tmp[28];		// ee;  odata[0] va al bit 1 del serializzatore
// assign odata[29:1] = odata_tmp[28:0];	// odata[26] va al bit27 del serializzatore	
// Guido Jan 2 2014
assign odata[29] = 1'b0;	
assign odata[28:0] = odata_tmp[28:0];	

assign bitmap_status = lamb_spare;

assign 	init_ev0_lamb0 = init_ev;
assign	init_ev1_lamb0 = init_ev;
assign	init_ev2_lamb0 = init_ev;
assign	init_ev0_lamb1 = init_ev;
assign	init_ev1_lamb1 = init_ev;
assign	init_ev2_lamb1 = init_ev;
assign	init_ev0_lamb2 = init_ev;
assign	init_ev1_lamb2 = init_ev;
assign	init_ev2_lamb2 = init_ev;
assign	init_ev0_lamb3 = init_ev;
assign	init_ev1_lamb3 = init_ev;
assign	init_ev2_lamb3 = init_ev;

assign resfifo0_ = 1'b1;
assign resfifo1_ = 1'b1;

/****************************************************************************
GLOBAL CLOCK BUFFER
*****************************************************************************/
BUFGP clk_buf(.O(int_clk),
				  .I(clk) 			//definisco il clock interno su un BUFG
				  );	

				
/****************************************************************************
x6ffctr: 	6 Fifo controllers for the 6 input Fifos.
*****************************************************************************/
x6ffctr fifoctr(int_clk,ef_b,init,pop,rden_b,reg_en, pok);


//*******************************
// VME control module
//*******************************
//wire [3:0] addr_opcode;
//wire [3:0] opcode_out;

vme vme_inst(		.clk(int_clk),
								.back_init(back_init),
								.geadd(geadd),
								.as_(as_b),
								.ds0_(ds0_b),
								.ds1_(ds1_b),
								.am(am),				// Address Mode
								.lword_(lword_b),
								.iack_(iack_b),
								.write_(write_b),
								.vadd(vadd),
								.vmedata(vme_data[31:0]),		// mp 27.11.2006
								.am_init(xxx_init), 		// init va in uscita dal chippone per resettare la scheda
								.tmode(tmode),  
								.edro_mode(edro_mode), 
								.start_rd_fifo(start_rd_fifo), 
								.hit_loop(hit_loop),
								.en_tck(),	 		// diventara' un segnale interno
								.tck_am_lamb0(tck_am_lamb0),
								.tck_am_lamb1(tck_am_lamb1),
								.tck_am_lamb2(tck_am_lamb2),
								.tck_am_lamb3(tck_am_lamb3),
								.wrpam(wrpam),
								.rdbscan(rdbscan),
								.wr_nloop(wr_nloop),
								.wr_input(wr_input),		// segnale interno: read/write registri di input delle 6 fifos
								.rd_input(rd_input),		// segnale interno: read/write registri di input delle 6 fifos
								.berr_(berr_b),
								.dtack_(dtack_b),
								.enb_(enb_b),
								.dirw_(dirw_b),
								.add(add),
								.rwadd(rwadd),
								.rd_vme(rd_vme),
		  					.ivdata(ivdata_vme),
		  					.ivadd(ivadd),		// latched vme signals. Out
		  					.ladd(ladd),
		  					.dr_(dr_),
		  					.hee_reg(hee_reg),
		  					.last_hreg_ee(last_hreg_ee),			// DEBUG
		  					.state(state),								// DEBUG
		  					.input_ctr_debug(input_ctr_debug), 	// DEBUG
		  					.freeze(freeze),
		  					.ospy_status(ospy_status),
		  					.ospy_sel(ospy_sel),
		  					.ospy_data_out(ospy_data_out),		//input for vme
		  					
		  					.ispy0_status(ispy0_status),
		  					.ispy0_sel(ispy0_sel),
		  					.ispy0_data_out(ispy0_data_out),
		  					
		  					.ispy1_status(ispy1_status),
		  					.ispy1_sel(ispy1_sel),
		  					.ispy1_data_out(ispy1_data_out),
		  					
		  					.ispy2_status(ispy2_status),
		  					.ispy2_sel(ispy2_sel),
		  					.ispy2_data_out(ispy2_data_out),
		  					
		  					.ispy3_status(ispy3_status),
		  					.ispy3_sel(ispy3_sel),
		  					.ispy3_data_out(ispy3_data_out),
		  					
		  					.ispy4_status(ispy4_status),
		  					.ispy4_sel(ispy4_sel),
		  					.ispy4_data_out(ispy4_data_out),
		  					
		  					.ispy5_status(ispy5_status),
		  					.ispy5_sel(ispy5_sel),
		  					.ispy5_data_out(ispy5_data_out),
		  					.hitmask(hitmask),
							
							.err_flag(err_flag),
							.err_critical(err_critical),
		  					
		  					.vme_block(vme_block),
							.count_patt(count_patt),
							.count_event(count_event),
							.init_stat_count(init_stat_count),
	
							.bitmap_en(bitmap_en),
							//for opcode
							//.addr_opcode(addr_opcode),
							.wr_opcode(wr_opcode)
							);
								

/****************************************************************************
Master: 	Finite State Machine
*****************************************************************************/
wire [5:0] rd_fifo;
wire [4:0] addr_rd_opc;
wire [4:0] addr_wr_opc;

FiniteStateMachine mainFSM  (	.clk(int_clk),
							.init(init),
							.pok(pok),		// pok e' un input per mainFSM
           				.dr(~dr_),  // messo il not  mp 22.04.2008
							//.rhold(rhold_b),		//hold for road is enble HIGH
							.rhold(logic_0),		//hold for road is enble HIGH
          				.init_iam(init_ev),
          				.rd_fifo(rd_fifo),
          				.rpush(rpush),
          				.sel_IAM(sel_loc_road),
							.need_opc_data(need_opc_data),
							.addr_wr_opc(addr_wr_opc),
							.addr_rd_opc(addr_rd_opc),
							.rd_opc_ram(rd_opc_ram),
           				.en(en),
           				.pop(pop),
           				.curr_state(state),
           				.last_hreg_ee(last_hreg_ee),
							.hee_reg(hee_reg), //insert signal of register hit 
							.finish_road(finish_road),
							//for statistic
							.count_patt(count_patt),
							.count_event(count_event),
							.init_stat_count(init_stat_count)
          		); 
	
	
		   
/****************************************************************************
input_ctr: 	receives hits from the 6 input Fifos.
*****************************************************************************/									
x6_input_hit  hitctr(		.clk(int_clk),
											.init(init),
											.init_ev(init_ev), 
											.lay0_in(lay0_in[17:0]),
											.lay1_in(lay1_in[17:0]),
											.lay2_in(lay2_in[17:0]),
											.lay3_in(lay3_in[17:0]),
											.lay4_in(lay4_in[17:0]),
											.lay5_in(lay5_in[17:0]),
											.new_hit(reg_en),
											.wr_hit_lamb(en), 
											.enA_wr(enA_wr),
											.enB_wr(enB_wr),
											.enC_wr(enC_wr),
											.enD_wr(enD_wr),
											.A0_HIT(A0_HIT),
											.A1_HIT(A1_HIT),
											.A2_HIT(A2_HIT),
											.A3_HIT(A3_HIT),
											.A4_HIT(A4_HIT),
											.A5_HIT(A5_HIT), 
											.B0_HIT(B0_HIT),
											.B1_HIT(B1_HIT),
											.B2_HIT(B2_HIT),
											.B3_HIT(B3_HIT),
											.B4_HIT(B4_HIT), // before ()
											.B5_HIT(B5_HIT), 
											.C0_HIT(C0_HIT),
											.C1_HIT(C1_HIT),
											.C2_HIT(C2_HIT),
											.C3_HIT(C3_HIT),
											.C4_HIT(C4_HIT),
											.C5_HIT(C5_HIT), 
											.D0_HIT(D0_HIT),
											.D1_HIT(D1_HIT),
											.D2_HIT(D2_HIT),
											.D3_HIT(D3_HIT),
											.D4_HIT(D4_HIT), // before ()
											.D5_HIT(D5_HIT), 
											.state(state),
											.tmode(tmode),
											.edro_mode(edro_mode),
											.start_rd_fifo(start_rd_fifo),
											.hit_loop(hit_loop),
											.vmedata(vme_data),
											.wr_nloop(wr_nloop),
											.vme_input0_fifo(vme_input0_fifo), 
											.vme_input1_fifo(vme_input1_fifo),
											.vme_input2_fifo(vme_input2_fifo),
											.vme_input3_fifo(vme_input3_fifo),
											.vme_input4_fifo(vme_input4_fifo),
											.vme_input5_fifo(vme_input5_fifo),
											.data_ispy0(data_ispy0),
											.data_ispy1(data_ispy1),
											.data_ispy2(data_ispy2),
											.data_ispy3(data_ispy3),
											.data_ispy4(data_ispy4),
											.data_ispy5(data_ispy5),
											.push_data_ispy(push_data_ispy),
											.wr_fifo(wr_fifo),
											.hitmask(xxx_hitmask), 
											.hee_reg(hee_reg),
											.HIT_lay0(HIT_lay0),
											.HIT_lay1(HIT_lay1),
											.HIT_lay2(HIT_lay2),
											.HIT_lay3(HIT_lay3),
											.HIT_lay4(HIT_lay4),
											.HIT_lay5(HIT_lay5),
											.push_hit(push),  //cambiare con il push in output
											.rd_fifo(rd_fifo),
											.tag_ee_word(curr_tag),		//generate tag for test VME or normal test
											.err_flag(err_flag),
											.err_critical(err_critical)
									);

//*******************************************************************************
// WRITE HIT VME
//*******************************************************************************
wr_fifo_hit		wr_fifo_hit_inst(	.clk(int_clk),
											.init(init),
											.vmedata(vme_data[19:0]),		
											.ivdata(ivdata_input),
											.wr_input(wr_input),
											.rwadd(rwadd),
											.vme_input0_fifo(vme_input0_fifo), 
											.vme_input1_fifo(vme_input1_fifo),
											.vme_input2_fifo(vme_input2_fifo),
											.vme_input3_fifo(vme_input3_fifo),
											.vme_input4_fifo(vme_input4_fifo),
											.vme_input5_fifo(vme_input5_fifo),
											.wr_fifo(wr_fifo),
											.input_ctr_debug(input_ctr_debug) 
										  );
										  
										  
//*******************************************************************************
// OPCODE RAM
//*******************************************************************************


opcode_storage		opcode_storage_inst( .clk(int_clk),
													.init(init),
													.opcode_in(vme_data[3:0]),
													.addr_wr_opc(addr_wr_opc),
													.addr_rd_opc(addr_rd_opc),
													.wr_opcode(wr_opcode),
													.rd_opc_ram(rd_opc_ram),
													.need_opc_data(need_opc_data),
													.opcode0_out(opcode0_out),
													.opcode1_out(opcode1_out),
													.opcode2_out(opcode2_out),
													.opcode3_out(opcode3_out)
													);
									

//*******************************************************************************
// AM GLUE
//*******************************************************************************
am_glue am_glue_inst(		.clk(int_clk),			
												.init(init),
												.dr0_b(dr0_b),
												.dr1_b(dr1_b),
												.dr2_b(dr2_b),
												.dr3_b(dr3_b),
												.ladd0(ladd0),
												.ladd1(ladd1),
												.ladd2(ladd2),
												.ladd3(ladd3),
												.sel0_b(sel0_b),  //output: e' un aknowledge per le lamb
												.sel1_b(sel1_b),
												.sel2_b(sel2_b),
												.sel3_b(sel3_b),
												.oadd(ladd),		// 23 bits
												.dr_b(dr_),  		// e' presente un road locale (proveniente dalle lamb)
												.bitmap_en(bitmap_en),
												.finish_road(finish_road),
												//.rhold(rhold_b)
												.rhold(logic_0)
												);
	
///****************************************************************************
//ROAD FLUX: Receives Roads from the LAMB (ladd) and sends them to the output 
//register (odata) together with data stobe wr_road. 
//Select the normal flux of the Roads from the LAMB or the End Event word	
//*****************************************************************************/   
road_flux  roadreg(  .clk(int_clk),                    
							.init(init),                      
							.rpush(rpush),                                
							.add(ladd),                                        
							.sel_word(sel_loc_road),            
							.tag_event(curr_tag),		                 
							.road_out(odata_tmp),             
							.wr_road(wr_road)                                 
							);	                              


// ********************
//   OUTPUT SPYBUFFER
// ********************
ospy ospy_inst		(	.clk(int_clk),
							.ospy_data_in(odata_tmp),		// spybuffer input data
							.reset_ospy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
							.push(wr_road),			// spybuffer write enable *****************
							.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
							.ospy_addr_sel(ospy_sel),	
							.freeze(freeze),
							.ospy_data_out(ospy_data_out),		// data out to vme
							.ospy_of(ospy_of),	// for ospy status
							.ospy_addr(ospy_addr)		// for ospy status
						);



// ********************
//   INPUT SPYBUFFER
// ********************
ispy ispy0_inst		(	.clk(int_clk),
								//.data_in(lay0_in_neg),
								.ispy_data_in(data_ispy0),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[0]),			// spybuffer write enable
								.push(push_data_ispy[0]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy0_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy0_data_out),		// data out to vme
								.ispy_of(ispy0_of),	// for ospy status
								.ispy_addr(ispy0_addr)		// for ospy status
						);			
						
ispy ispy1_inst		(	.clk(int_clk),
								//.data_in(lay1_in),
								.ispy_data_in(data_ispy1),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[1]),			// spybuffer write enable
								.push(push_data_ispy[1]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy1_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy1_data_out),		// data out to vme
								.ispy_of(ispy1_of),	// for ospy status
								.ispy_addr(ispy1_addr)		// for ospy status
						);												
		

ispy ispy2_inst		(	.clk(int_clk),
								//.data_in(lay2_in),
								.ispy_data_in(data_ispy2),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[2]),			// spybuffer write enable
								.push(push_data_ispy[2]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy2_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy2_data_out),		// data out to vme
								.ispy_of(ispy2_of),	// for ospy status
								.ispy_addr(ispy2_addr)		// for ospy status
							);			
						
						
						
						
ispy ispy3_inst		(	.clk(int_clk),
								//.data_in(lay3_in),
								.ispy_data_in(data_ispy3),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[3]),			// spybuffer write enable
								.push(push_data_ispy[3]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy3_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy3_data_out),		// data out to vme
								.ispy_of(ispy3_of),	// for ospy status
								.ispy_addr(ispy3_addr)		// for ospy status
						);									
						

ispy ispy4_inst		(	.clk(int_clk),
								//.data_in(lay4_in),
								.ispy_data_in(data_ispy4),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[4]),			// spybuffer write enable
								.push(push_data_ispy[4]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy4_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy4_data_out),		// data out to vme
								.ispy_of(ispy4_of),	// for ospy status
								.ispy_addr(ispy4_addr)		// for ospy status
						);			
						
						
ispy ispy5_inst		(	.clk(int_clk),
								//.data_in(lay5_in),
								.ispy_data_in(data_ispy5),		// spybuffer input data
								.reset_ispy_data(init),		// provvisorio. forse serve un reset ad hoc. Vedere svt
								//.push(reg_en[5]),			// spybuffer write enable
								.push(push_data_ispy[5]),
								.VMEaddr(ivadd[11:2]),				// spybuffer vme read address
								.ispy_addr_sel(ispy5_sel),	
								.freeze(freeze),
								.ispy_data_out(ispy5_data_out),		// data out to vme
								.ispy_of(ispy5_of),	// for ospy status
								.ispy_addr(ispy5_addr)		// for ospy status
						);									
						


////////////////////////////////
// DEBUG
///////////////////////////////

// instanzio chipscope_ctr										
wire [35:0] control0_sig;
wire [35:0] control1_sig;
wire [35:0] control2_sig;
//wire [35:0] control3_sig;

wire [78:0] vme_block_debug = {vme_block, vme_data, vadd, 1'b0};

// Guido
// chipscope_ctr	chipscope_ctr_inst	(.CONTROL0(control0_sig),
//																  .CONTROL1(control1_sig),
//																	.CONTROL2(control2_sig)
//																  .CONTROL2(control3_sig)
//																	.CONTROL4(control4_sig)
//																	); 
// istanzio chipscope_vme_blobk
// Guido
// chipscope_vme_block	chipscope_vme_block_inst	(.CLK(int_clk),
//																			.CONTROL(control1_sig),
//																			.TRIG0(vme_block_debug)
//																			);

// istanzio chipscope_LA_in
//chipscope_LA_in	chipscope_LA_in_inst	(.CLK(int_clk),
//																			.CONTROL(control0_sig),
//																			.TRIG0(lay0_in_neg),
//																			.TRIG1(ef_),
//																			.TRIG2(rden_)
//																			);

// istanzio chipscope_LA_in
// Guido
// chipscope_HIT_push	chipscope_HIT_push_inst	(.CLK(int_clk),
//																			.CONTROL(control0_sig),
//																			.TRIG0(push[4]),
//																			.TRIG1(HIT_lay4)
//																			);


// istanzio chipscope_LA_in_lamb
//chipscope_LA_in_lamb	chipscope_LA_in_lamb_inst	(.CLK(int_clk),
//																								.CONTROL(control1_sig),
//																								.TRIG0(A0_HIT),
//																								.TRIG1(enA_wr[0])
//																									);

wire [3:0] debug_fsm = {state, finish_road};
// instanzio chipscope_LA_out_lamb
// Guido
// chipscope_LA_out_lamb	chipscope_LA_out_lamb_inst	(.CLK(int_clk),
//																									.CONTROL(control2_sig),
//																									.TRIG0(ladd2),	
//																									.TRIG1(dr2_),
//																									.TRIG2(sel2_),
//																									.TRIG3(init_ev0_lamb2),
//																									.TRIG4(debug_fsm),
//																									.TRIG5(rpush)
//																									);
												
												
// istanzio chipscope_LA_out
//chipscope_LA_out	chipscope_LA_out_inst	(.CLK(int_clk),
//																					.CONTROL(control3_sig),
//																					.TRIG0(odata_tmp),	//mp 27.07.2010
//																					.TRIG1(wr_road)
//																					);										
					
endmodule
/* ========================================================================  */
