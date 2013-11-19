calculate-features-vector
=========================

test for uci data set--  Localization Data for Person Activity Data Set,  calculate the features vector [x[n], y[n], z[n], SMV[n], SMA[n]].  

The features vector are  SMV, SMA, the angle of acceleration.

SMV is defined as 
                                                    SMV = sqrt(x^2,y^2,z^2)
                                                    -----------------------
        
SMA is defined as 
               SMA[n] = 1/N( x[n]+x[n-1]+...+x[n-N+1] + y[n]+y[n-1]+...+y[n-N+1] + z[n]+z[n-1]+...+z[n-N+1]
               --------------------------------------------------------------------------------------------
              
N is the last data record nums. 
