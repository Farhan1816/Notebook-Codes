 //sum over subset
  for(int i=0;i<20;i++){
    for(int j=0;j<N;j++){
      if((j&(1<<i))){
        dp1[j] += dp1[(j^(1<<i))];
      }
    }
  }

  //sum of superset
  for(int i=0;i<20;i++){
    for(int j=0;j<N;j++){
      if(!(j&(1<<i))){
        dp2[j] += dp2[(j^(1<<i))];
      }
    }
  }
