
/*****SECTOR VARIABLES RELATED TO THE EXTERNAL SECTOR*****/


EQUATION("Sector_External_Price")
/*
External price of the sector's goods. 
*/
	v[0]=VL("Sector_External_Price",1);						//external price in the last period
	v[1]=V("external_price_growth");						//exogenous external price rate of growth
	if(v[1]!=0)												//if the exogenous rate is different from zero
		v[2]=(1+v[1])*v[0];									//apply the exogenous rate of growth
	else													//if not (endogenous rate of growth)
   	{     
		v[3]=VL("Sector_Avg_Price",2);						//sector average price lagged 2
		v[4]=VL("Sector_Avg_Price",1);						//sector average price lalged 1
		v[5]=V("external_price_competitiveness");			//parameter that determines how domestic sector is competitive and affect external price
		v[2]=v[0]*(1+v[5]*((v[4]-v[3])/v[3]));				//new external price will depend on the rate of growth of domestic price
   	}  
RESULT(v[2])


EQUATION("Sector_Exports")
/*
Real exports are defined for each sector based on the application of an export coefficient on external income. 
*/
	v[0]=V("External_Income");								//external income										
	v[1]=V("sector_exports_coefficient");					//sector especific exports coefficent				
	v[2]=V("Sector_Avg_Price");								//sector average price			
	v[3]=V("Sector_External_Price");						//external price
	v[4]=V("exports_elasticity_income");					//sector specific income elasticity
	v[5]=V("exports_elasticity_price");						//sector specific price elasticity
	v[6]=V("Exchange_Rate");								//current exchange rate
	v[7]=v[1]*pow((v[3]*v[6])/v[2],v[5])*pow(v[0],v[4]);	//sector exports will depend on the relative prices and external income, given the elasticities
RESULT(v[7])


EQUATION("Sector_Extra_Imports")
/*
The extra import, if the sector can not meet its internal demand, is determined by the difference between the actual orders of the sector and its actual production plus the available stock of products. 
The value of these imports is obtained by multiplying the previous result by the external price of the inputs of the sector in question.
EQUATION TO BE IMPROVED IN THE FUTURE
*/
	v[0]=V("Sector_Consumption_Demand");					//sector consumption demand (zero if not consumption good sector)
	v[1]=V("Sector_Capital_Demand");						//sector capital demand (zero if not capital good sector)
	v[2]=V("Sector_Intermediate_Demand");					//sector intermediate demand (zero if not intermediate goods sector)
	v[3]=V("Sector_Demand_Met");							//percentage of demand met by the domestic production
	v[4]=(v[0]+v[1]+v[2])*(1-v[3]);							//demand not met
	v[5]=VL("International_Reserves",1);					//current stock of international reserves (usually not a constraint in baseline simulations)
	if(v[4]>0)												//if there is demand not met
		{
		if(v[5]>0)											//check if there is reserves. if yes									
			{
			v[6]=v[4];										//value of unmet demand is bought as extra imports
			v[7]=1;											//mark as 1 the variable that identifies if demand was met by imports
			}
		else												//if there is no reserves
			{
			v[6]=0;											//no extra imports
			v[7]=0;											//mark as zero the variable that identifies that demand was met by imports
			}
		WRITE("Sector_Demand_Met_By_Imports", v[7]);		//write the variable that identifies that demand was met by imports
		}
	else													//if there is no unmet demand
		v[6]=0;												//no extra imports											
RESULT(v[6])

EQUATION_DUMMY("Sector_Demand_Met_By_Imports", "Sector_Extra_Imports")



