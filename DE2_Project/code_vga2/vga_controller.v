module vga_controller(iRST_n,
                      iVGA_CLK,
                      oBLANK_n,
                      oHS,
                      oVS,
                      b_data,
                      g_data,
                      r_data);
input iRST_n;
input iVGA_CLK;
output reg oBLANK_n;
output reg oHS;
output reg oVS;
output [7:0] b_data;
output [7:0] g_data;
output [7:0] r_data;
///////// ////
reg [18:0] ADDR;
reg [23:0] bgr_data;
wire VGA_CLK_n;
wire [7:0] index;
wire [23:0] bgr_data_raw;
wire cBLANK_n,cHS,cVS,rst;
////
assign rst = ~iRST_n;
video_sync_generator LTM_ins (.vga_clk(iVGA_CLK),
                              .reset(rst),
                              .blank_n(cBLANK_n),
                              .HS(cHS),
                              .VS(cVS));

///YT   显示图片
////
////Addresss generator
always@(posedge iVGA_CLK,negedge iRST_n)
begin
  if (!iRST_n)
     ADDR<=19'd0;
  else if (cHS==1'b0 && cVS==1'b0)
     ADDR<=19'd0;
  else if (cBLANK_n==1'b1)
     ADDR<=ADDR+1;
end
//////////////////////////
//////INDEX addr.
assign VGA_CLK_n = ~iVGA_CLK;    

	img_pic inst_img_pic (.address(ADDR), .clock(iVGA_CLK), .q(bgr_data_raw));


// // rom: 8bit 307200words   M9K   img_data_logo.mif
// img_data	img_data_inst (
// 	.address ( ADDR ),
// 	.clock ( VGA_CLK_n ),
// 	.q ( index )
// 	);
// //////Color table output
// // rom: 24bit 256words   M9K   index_logo.mif
// img_index	img_index_inst (
// 	.address ( index ),
// 	.clock ( iVGA_CLK ),
// 	.q ( bgr_data_raw)
// 	);	
// //////

//////latch valid data at falling edge;
always@(posedge VGA_CLK_n) bgr_data <= bgr_data_raw;
assign b_data = bgr_data[23:16];
assign g_data = bgr_data[15:8];
assign r_data = bgr_data[7:0];
///////////////////
//////Delay the iHD, iVD,iDEN for one clock cycle;
always@(negedge iVGA_CLK)
begin
  oHS<=cHS;
  oVS<=cVS;
  oBLANK_n<=cBLANK_n;
end


//YT   color block
//-----------------------------------------------------------       
// reg[7:0] vga_rdb;
// reg[7:0] vga_gdb;
// reg[7:0] vga_bdb;

// always @(posedge iVGA_CLK or negedge iRST_n)
//   if(!iRST_n) begin
//     vga_rdb <= 8'd0;
//     vga_gdb <= 8'd0;
//     vga_bdb <= 8'd0;
//   end
//   else if(xcnt == (VGA_HST+VGA_HBP-1)) begin                
//     vga_rdb <= 8'h0;
//     vga_gdb <= 8'h3f;
//     vga_bdb <= 8'd0;    
//   end
//   else if(xcnt == (VGA_HST+VGA_HBP+VGA_HVT-1'b1)) begin         
//     vga_rdb <= 8'h0;
//     vga_gdb <= 8'h3f;
//     vga_bdb <= 8'd0;    
//   end
//   else if(ycnt == (VGA_VST+VGA_VBP-1)) begin                
//     vga_rdb <= 8'h0;
//     vga_gdb <= 8'h3f;
//     vga_bdb <= 8'd0;    
//   end
//   else if(ycnt == (VGA_VST+VGA_VBP+VGA_VVT-1'b1)) begin         
//     vga_rdb <= 8'h0;
//     vga_gdb <= 8'h3f;
//     vga_bdb <= 8'd0;    
//   end
//   else begin                                
//     vga_rdb <= 8'h1f;
//     vga_gdb <= 8'd0;
//     vga_bdb <= 8'd0;  
//   end

// //-----------------------------------------------------------       
// assign r_data = cBLANK_n ? vga_rdb:8'd0;
// assign g_data = cBLANK_n ? vga_gdb:8'd0;  
// assign b_data = cBLANK_n ? vga_bdb:8'd0;  



endmodule
 	
















