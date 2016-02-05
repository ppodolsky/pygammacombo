
TString varToTex(TString var)
{
  if ( var == "R_dk_vs_dpi"             ) return "$R_{K/\\pi}^{K\\pi\\pi\\pi}$";
  if ( var == "A_FAV_b2dk_d2kpipipi"    ) return "$A_{K}^{K\\pi\\pi\\pi}$";
  if ( var == "A_FAV_b2dpi_d2kpipipi"   ) return "$A_{\\pi}^{K\\pi\\pi\\pi}$";
  if ( var == "R_plus_b2dk_d2pikpipi"   ) return "$R_{K-}^{\\pi K\\pi\\pi}$";
  if ( var == "R_minus_b2dk_d2pikpipi"  ) return "$R_{K+}^{\\pi K\\pi\\pi}$";
  if ( var == "R_plus_b2dpi_d2pikpipi"  ) return "$R_{\\pi-}^{\\pi K\\pi\\pi}$";
  if ( var == "R_minus_b2dpi_d2pikpipi" ) return "$R_{\\pi+}^{\\pi K\\pi\\pi}$";
}

void getDk3piGLWADScor()
{
	TFile *f = TFile::Open("sept2012K3PIResult.root");
  RooFitResult *r = (RooFitResult*)f->Get("fitresult_model_reducedData_binned");
  
  TString vars[] = {
    "R_dk_vs_dpi"            ,
    "A_FAV_b2dk_d2kpipipi"   ,
    "A_FAV_b2dpi_d2kpipipi"  ,
    "R_plus_b2dk_d2pikpipi"  ,
    "R_minus_b2dk_d2pikpipi" ,
    "R_plus_b2dpi_d2pikpipi" ,
    "R_minus_b2dpi_d2pikpipi"
  };
  
  // for ( int i=0; i<13; i++ )
  // {
  //   printf("%20s", vars[i].Data());
  //   for ( int j=0; j<13; j++ )
  //   {
  //     float c = r->correlation(vars[i], vars[j]);
  //     // if ( fabs(c)<0.01 ) continue;
  //     // printf("%20s : %20s = %6.3f\n", vars[i].Data(), vars[j].Data(), c);
  //     if ( fabs(c)<0.00049 ) 
  //       printf("%7s", "");
  //     else 
  //       printf("%7.3f", c);
  //   }
  //   cout << endl;
  // }

  //
  // LATEX PRINTOUT
  //
  int n = 7;
  for ( int i=0; i<n; i++ )
  {
    printf(" & %20s ", varToTex(vars[i]).Data());
  }
  cout << "\\\\" << endl;
  cout << "\\hline" << endl;

  for ( int i=0; i<n; i++ )
  {
    printf("%24s & ", varToTex(vars[i]).Data());
    for ( int j=0; j<n; j++ )
    {
      float c = r->correlation(vars[i], vars[j]);
      if ( j>=i )
        if ( fabs(c)<0.001 ) printf("%7.0f ", 0);
        else if ( c==1 )    printf("%7.0f ", 1);
        else printf("%7.3f ", c);
      else
        printf("%7s ", " ");
      if ( j<n-1 ) cout << "&";
    }
    cout << "\\\\" << endl;
  }
}
