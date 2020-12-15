
/******MACRO FUNCTIONS******/


EQUATION("Income_Taxes_Function")
/*
Calculates income taxes of the classes and must be called by the government variable
Must be called by Government.
*/
	v[0]=V("Total_Wages");                                 		//total wages          
	v[1]=V("Total_Distributed_Profits");                         		//distributed profits for the classes
	v[2]=0;                                               		//initializes the CYCLE
	CYCLE(cur, "CLASSES")                                 		//CYCLE trought all classes
	{
		v[3]=VS(cur,"class_direct_tax");                     	//income tax percentage of each class
		v[4]=VS(cur,"class_profit_share");                   	//class profit share
		v[5]=VS(cur,"class_wage_share");                     	//class wage share
		v[6]=(v[0]*v[5]+v[1]*v[4])*v[3];                     	//income tax of each class is the tax percentage multiplyed by class total income
		v[2]=v[2]+v[6];                                     	//sums up income taxes of all classes
	}
RESULT(v[2])


EQUATION("Indirect_Taxes_Function")
/*
Calculates indirect taxes of all firms. Must be called by the government variable
Must be called by Government.
*/
	v[0]=0;                                						//initializes the CYCLE
	CYCLE(cur, "SECTORS")                  						//CYCLE trought all sectors
	{              
		v[1]=0;                              					//initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")           					//CYCLE trought all firms in the sector
		{
			v[2]=VS(cur1, "Firm_Indirect_Tax");     			//firm's indirect tax
			v[1]=v[1]+v[2];                    					//sums up all firm's indirect tax of the sector
		}
	v[0]=v[0]+v[1];                        						//sums up all sectors indirect tax
	}
RESULT(v[0])



