/*****PRODUCTION AND DEMAND*****/


EQUATION("Sector_Intermediate_Demand")
/*
Depends on the total domestic intermediate demand, if it is a intermediate goods sector.
*/
	if(V("id_intermediate_goods_sector")==1)								//if it is intermediate goods sector
	{
		v[0]=0;                                                      		//initializes the value for thr CYCLE
		CYCLES(root, cur, "SECTORS")                                        //CYCLE trought all sectors
		{
			v[1]=0;                                                    		//initializes the value for the CYCLE
			CYCLES(cur, cur1, "FIRMS")                                 		//CYCLE trought all firms inside the sectors
			{    
				v[2]=VS(cur1, "Firm_Input_Demand_Next_Period");             //gives the demand for imputs of each firm
				v[1]=v[1]+v[2];                                          	//sums up the demand for imputs of all firms
			} 
		v[0]=v[0]+v[1];                                              		//sums up the demand for imputs of all setors
		}
	}
	else																	//if not
		v[0]=0;																//sector intermediate demand is zero
RESULT(v[0])


EQUATION("Sector_Consumption_Demand") 
/*
Depends on the total domestic consumption demand, if it is a consumption goods sector.
*/

	if(V("id_consumption_goods_sector")==1)                     //if it is a consumption good sector
	{
		v[0]=0;                                                 //initializes the CYCLE
		CYCLES(root,cur, "CLASSES")                             //CYCLE trought all income classes
		{
			v[1]=VS(cur, "Class_Real_Domestic_Consumption");    //class consumption
			v[0]=v[0]+v[1];                                     //sums up all classes consumption
		}
	}
	else                                                    	//if it is not a consumption good sector 
		v[0]=0;                                               	//sector consumption demand is zero
RESULT(v[0])


EQUATION("Sector_Capital_Demand")
/*
Depends on the total domestic capital demand, if it is a capital goods sector.
*/

	if(V("id_capital_goods_sector")==1)											//if it is a capital good sector
	{
		v[1]=0;                                                 				//initializes the CYCLE
		CYCLES(root, cur, "SECTORS")                                   			//CYCLE trought the sectors
		{	
			v[2]=0;                                               				//initializes the second CYCLE
			CYCLES(cur, cur1, "FIRMS")                            				//CYCLE trought the firms
			{
				v[3]=VS(cur1, "Firm_Demand_Capital_Goods");         			//gives the demand for capital goods of each firm
				v[2]=v[2]+v[3];                                    				//sums up all capital goods demand
			}
			v[1]=v[1]+v[2];                                       				//sums up all firm's capital goods demand
		}		
	}
	else																		//if not 
		v[1]=0;																	//sector capital demand is zero
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
