
TString varToTex(TString var)
{
  if ( var ==     "A_CPP_b2dk_d2kk" ) return "$A_{K}^{KK}$";
  if ( var ==    "A_CPP_b2dpi_d2kk" ) return "$A_{\\pi}^{KK}$";
  if ( var ==   "A_CPP_b2dk_d2pipi" ) return "$A_{K}^{\\pi\\pi}$";
  if ( var ==  "A_CPP_b2dpi_d2pipi" ) return "$A_{\\pi}^{\\pi\\pi}$";
  if ( var ==    "A_FAV_b2dk_d2kpi" ) return "$A_{K}^{K\\pi}$";
  if ( var ==   "A_FAV_b2dpi_d2kpi" ) return "$A_{\\pi}^{K\\pi}$";
  if ( var ==  "R_dk_vs_dpi_d2pipi" ) return "$R_{K/\\pi}^{\\pi\\pi}$";
  if ( var ==    "R_dk_vs_dpi_d2kk" ) return "$R_{K/\\pi}^{KK}$";
  if ( var ==   "R_dk_vs_dpi_d2kpi" ) return "$R_{K/\\pi}^{K\\pi}$";
  if ( var ==  "R_minus_b2dk_d2pik" ) return "$R_{K}^-$";
  if ( var == "R_minus_b2dpi_d2pik" ) return "$R_{\\pi}^-$";
  if ( var ==   "R_plus_b2dk_d2pik" ) return "$R_{K}^+$";
  if ( var ==  "R_plus_b2dpi_d2pik" ) return "$R_{\\pi}^+$";
}

void getGLWADScor()
{
	TFile *f = TFile::Open("winter2012ADSGLWResult.root");
  RooFitResult *r = (RooFitResult*)f->Get("fitresult_model_reducedData_binned");
  
  TString vars[] = {
        "A_CPP_b2dk_d2kk",
       "A_CPP_b2dpi_d2kk",
      "A_CPP_b2dk_d2pipi",
     "A_CPP_b2dpi_d2pipi",
       "A_FAV_b2dk_d2kpi",
      "A_FAV_b2dpi_d2kpi",
     "R_dk_vs_dpi_d2pipi",
       "R_dk_vs_dpi_d2kk",
      "R_dk_vs_dpi_d2kpi",
     "R_minus_b2dk_d2pik",
    "R_minus_b2dpi_d2pik",
      "R_plus_b2dk_d2pik",
     "R_plus_b2dpi_d2pik"
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
  for ( int i=0; i<13; i++ )
  {
    printf(" & %20s ", varToTex(vars[i]).Data());
  }
  cout << "\\\\" << endl;
  cout << "\\hline" << endl;

  for ( int i=0; i<13; i++ )
  {
    printf("%20s & ", varToTex(vars[i]).Data());
    for ( int j=0; j<13; j++ )
    {
      float c = r->correlation(vars[i], vars[j]);
      if ( j>=i )
        if ( fabs(c)<0.001 ) printf("%7.0f ", 0);
        else if ( c==1 )    printf("%7.0f ", 1);
        else printf("%7.3f ", c);
      else
        printf("%7s ", " ");
      if ( j<12 ) cout << "&";
    }
    cout << "\\\\" << endl;
  }
}
