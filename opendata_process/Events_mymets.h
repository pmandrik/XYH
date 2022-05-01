//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  1 00:25:24 2022 by ROOT version 6.26/02
// from TTree Events_mymets/Events
// found on file: /home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root
//////////////////////////////////////////////////////////

#ifndef Events_mymets_h
#define Events_mymets_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Events_mymets {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         met_e;
   Float_t         met_pt;
   Float_t         met_px;
   Float_t         met_py;
   Float_t         met_phi;
   Float_t         met_significance;
   Float_t         met_rawpt;
   Float_t         met_rawphi;
   Float_t         met_rawe;

   // List of branches
   TBranch        *b_met_e;   //!
   TBranch        *b_met_pt;   //!
   TBranch        *b_met_px;   //!
   TBranch        *b_met_py;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_met_significance;   //!
   TBranch        *b_met_rawpt;   //!
   TBranch        *b_met_rawphi;   //!
   TBranch        *b_met_rawe;   //!

   Events_mymets(TTree *tree=0);
   virtual ~Events_mymets();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_mymets_cxx
Events_mymets::Events_mymets(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root:/mymets");
      dir->GetObject("Events_mymets",tree);

   }
   Init(tree);
}

Events_mymets::~Events_mymets()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events_mymets::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events_mymets::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Events_mymets::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("met_e", &met_e, &b_met_e);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_px", &met_px, &b_met_px);
   fChain->SetBranchAddress("met_py", &met_py, &b_met_py);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_significance", &met_significance, &b_met_significance);
   fChain->SetBranchAddress("met_rawpt", &met_rawpt, &b_met_rawpt);
   fChain->SetBranchAddress("met_rawphi", &met_rawphi, &b_met_rawphi);
   fChain->SetBranchAddress("met_rawe", &met_rawe, &b_met_rawe);
   Notify();
}

Bool_t Events_mymets::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events_mymets::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events_mymets::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_mymets_cxx
