biased = FALSE
a <- 1
b <- 2*3+a
var1 <- 5^2


if (biased)
{
    n <- length(x)
    (n - 1)/n * var(x)
}
else{
    x <- exp(-x^2/2)
    for (i in 1:50)
    {
        if ( i %% 5 == 0 )
        {
            print(i)
        }
    }
}   


test <- function(){
    if (a < 4)
    {
        a <- 5 
    }
    else {
        for ( a in 1:4){
            a <- 4
        }
    }
}
