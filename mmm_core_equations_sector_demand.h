/*****PRODUCTION AND DEMAND*****/


EQUATION("Sector_Intermediate_Demand")
/*
Depends on the total domestic intermediate demand, if it is a intermediate goods sector.
*/
	v[0]=V("id_intermediate_goods_sector");					    //identifies if it is intermediate goods sector
	if(v[0]==1)													//if yes
		v[1]=V("Total_Domestic_Intermediate_Demand");			//sector demand is equal to total intermediate demand
	else														//if not
		v[1]=0;													//sector demand is zero
RESULT(v[1])


EQUATION("Sector_Consumption_Demand") 
/*
Depends on the total domestic consumption demand, if it is a consumption goods sector.
*/
	v[0]=V("id_consumption_goods_sector");                  	//identifies consumption goods sector
	if(v[0]==1)                                             	//if it is a consumption good sector
		v[1]=V("Total_Domestic_Consumption_Demand");       		//sector demand is equal to total consumption demand 
	else                                                    	//if it is not a consumption good sector 
		v[1]=0;                                               	//domestic consumption is zero
RESULT(v[1])


EQUATION("Sector_Capital_Demand")
/*
Depends on the total domestic capital demand, if it is a capital goods sector.
*/
	v[0]=V("id_capital_goods_sector");							//identifies capital goods sector
	if(v[0]==1)													//if it is a capital good sector
		v[1]=V("Total_Domestic_Capital_Goods_Demand");			//sector demand is equal to total capital demand
	else														//if not 
		v[1]=0;													//sector demand is zero
RESULT(v[1])


EQUATION("Sector_Effective_Orders")
/*
Effective orders are determined from total demand for the products in the sector. 
In the sum of consumption goods, capital goods and intermediate goods, only the factor referring to the sector that is calling this variable will asume positive values. 
*/
	v[0]=V("Sector_Consumption_Demand");                        //domestic demand of consumption goods
	v[1]=V("Sector_Capital_Demand");                            //domestic demand of capital goods
	v[2]=V("Sector_Intermediate_Demand");                       //domestic demand of intermediate goods
	v[3]=v[0]+v[1]+v[2];                                        //sums up the domestic demands. For each sector, only the relevant demand will have a value and the others will be zero.
	v[4]=V("Sector_Exports");                                   //external demand, exports of the sector 
	v[5]=v[3]+v[4];                                             //sums up domestic and external demand
RESULT(max(0,v[5]))


EQUATION("Firm_Effective_Orders_Capital_Goods")
/*
Firm variable
Must be calculated first and specifically
*/
	
	v[1]=V("id_capital_goods_sector"); 							//identify capital good sector  
	if(v[1]==1)													//if it is
	{
		v[2]=V("Firm_Market_Share"); 							//firm market share
		v[3]=V("Sector_Effective_Orders");						//total sectoral orders
		v[4]=v[3]*v[2];											//firm orders will be total sectoral orders times market share
	}
	else														//if not capital good sector
		v[4]=0;   												//firm orders will be zero.   
RESULT(v[4])


EQUATION("Firm_Effective_Orders")
/*
Firm Variable
Determines that firm's demand.
*/
	v[0]=V("Firm_Market_Share"); 								//firm market share
	v[1]=V("Sector_Effective_Orders");							//total sectoral orders
	v[2]=v[0]*v[1];												//firm orders will be total sectoral orders times market share
RESULT(v[2])
