#include <stdlib.h>

#include "TApplication.h"
#include "TProof.h"
#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"

// The selectors
static TString gTutDir = "$ROOTSYS/tutorials"; // default path
static TString gH1Sel("/tree/h1analysis.C");
static TString gSimpleSel("/proof/ProofSimple.C");

int myProof(const char *url, const char *tut, const char *opt = 0, long long evts = 100000);

//_____________________________batch only_____________________
#ifndef __CINT__
int main(int argc,const char *argv[])
{

   bool enablegraphics = 0;
   const char *url = "lite://";
   const char *tut = "simple";
   const char *opt = 0;
   long long evts = 1000000;
   Int_t i = 1;
   while (i < argc) {
      if (!strcmp(argv[i],"-g")) {
         // Enable graphics
      	 enablegraphics = 1;
         i++;
      } else if (!strcmp(argv[i],"-n")) {
         // Options for proof
         if (i+1 == argc || argv[i+1][0] == '-') {
            printf(" -o should be followed by the number of events: ignoring \n");
            i++;
         } else { 
            evts = atoll(argv[i+1]);
            i += 2;
         }
      } else if (!strcmp(argv[i],"-t")) {
         // Tutorial to be run
         if (i+1 == argc || argv[i+1][0] == '-') {
            printf(" -t should be followed by the tutorial name: ignoring \n");
            i++;
         } else { 
            tut = argv[i+1];
            i += 2;
         }
      } else if (!strcmp(argv[i],"-o")) {
         // Options for proof
         if (i+1 == argc || argv[i+1][0] == '-') {
            printf(" -o should be followed by a string with options for PROOF: ignoring \n");
            i++;
         } else { 
            opt = argv[i+1];
            i += 2;
         }
      } else if (!strcmp(argv[i],"-tut")) {
         if (i+1 == argc || argv[i+1][0] == '-') {
            printf(" -tut should be followed by a path: ignoring \n");
            i++;
         } else { 
            gTutDir = argv[i+1];
            i += 2;
         }
      } else {
         url = argv[i];
         i++;
      }
   }

   // Enable graphics if required
   if (enablegraphics) {
      new TApplication("myProof", 0, 0);
   } else {
      gROOT->SetBatch(kTRUE);
   }

   int rc = myProof(url, tut, opt, evts);

   gSystem->Exit(rc);

}
#endif

//______________________________________________________________
int myProof(const char *url, const char *tut, const char *opt, long long evts)
{
	// Run PROOF tutorials

	// Start PROOF
	TProof *proof = TProof::Open(url, opt);
	if (!proof || !proof->IsValid()) {
	   printf("Could not open PROOF session at %s", url);
	   return -1;
	}

    TString sel, selh;
    Bool_t dodelete = kFALSE;
    // Run the requested tutorial
    if (!strcmp(tut, "simple")) {
       // Process the simple selector
       sel.Form("%s/%s", gTutDir.Data(), gSimpleSel.Data());
       gSystem->ExpandPathName(sel);
       // If the directory with the selector is not writable, copy it locally
       TString seldir = gSystem->DirName(sel);
       if (gSystem->AccessPathName(seldir, kWritePermission)) {
       	  selh = sel;
       	  selh.ReplaceAll(".C", ".h");
       	  TString loc = gSystem->BaseName(sel);
       	  gSystem->CopyFile(sel, loc, kTRUE);
       	  sel = loc;
       	  loc = gSystem->BaseName(selh);
       	  gSystem->CopyFile(selh, loc, kTRUE);
       	  selh = loc;
       	  dodelete = kTRUE;
       } 
       // The number of histograms is added as parameter in the input list
       proof->SetParameter("ProofSimple_NHist", (Long_t)64);
       proof->Process(sel, evts);
       if (dodelete) {
       	  gSystem->Unlink(sel);
       	  gSystem->Unlink(selh);
       }
    } else {
       printf("Unknown or unimplemented tutorial: %s", tut);
    }

    // Done
    return 0;
}

