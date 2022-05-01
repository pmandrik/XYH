//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  1 00:25:23 2022 by ROOT version 6.26/02
// from TTree Events_myelectrons/Events
// found on file: /home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root
//////////////////////////////////////////////////////////

#ifndef Events_myelectrons_h
#define Events_myelectrons_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Events_myelectrons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           numberelectron;
   vector<float>   *electron_e;
   vector<float>   *electron_pt;
   vector<float>   *electron_px;
   vector<float>   *electron_py;
   vector<float>   *electron_pz;
   vector<float>   *electron_eta;
   vector<float>   *electron_phi;
   vector<float>   *electron_ch;
   vector<float>   *electron_iso;
   vector<bool>    *electron_isLoose;
   vector<bool>    *electron_isMedium;
   vector<bool>    *electron_isTight;
   vector<float>   *electron_dxy;
   vector<float>   *electron_dz;
   vector<float>   *electron_dxyError;
   vector<float>   *electron_dzError;

   // List of branches
   TBranch        *b_numberelectron;   //!
   TBranch        *b_electron_e;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_px;   //!
   TBranch        *b_electron_py;   //!
   TBranch        *b_electron_pz;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_ch;   //!
   TBranch        *b_electron_iso;   //!
   TBranch        *b_electron_isLoose;   //!
   TBranch        *b_electron_isMedium;   //!
   TBranch        *b_electron_isTight;   //!
   TBranch        *b_electron_dxy;   //!
   TBranch        *b_electron_dz;   //!
   TBranch        *b_electron_dxyError;   //!
   TBranch        *b_electron_dzError;   //!

   Events_myelectrons(TTree *tree=0);
   virtual ~Events_myelectrons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_myelectrons_cxx
Events_myelectrons::Events_myelectrons(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root:/myelectrons");
      dir->GetObject("Events_myelectrons",tree);

   }
   Init(tree);
}

Events_myelectrons::~Events_myelectrons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events_myelectrons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events_myelectrons::LoadTree(Long64_t entry)
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

void Events_myelectrons::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   electron_e = 0;
   electron_pt = 0;
   electron_px = 0;
   electron_py = 0;
   electron_pz = 0;
   electron_eta = 0;
   electron_phi = 0;
   electron_ch = 0;
   electron_iso = 0;
   electron_isLoose = 0;
   electron_isMedium = 0;
   electron_isTight = 0;
   electron_dxy = 0;
   electron_dz = 0;
   electron_dxyError = 0;
   electron_dzError = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numberelectron", &numberelectron, &b_numberelectron);
   fChain->SetBranchAddress("electron_e", &electron_e, &b_electron_e);
   fChain->SetBranchAddress("electron_pt", &electron_pt, &b_electron_pt);
   fChain->SetBranchAddress("electron_px", &electron_px, &b_electron_px);
   fChain->SetBranchAddress("electron_py", &electron_py, &b_electron_py);
   fChain->SetBranchAddress("electron_pz", &electron_pz, &b_electron_pz);
   fChain->SetBranchAddress("electron_eta", &electron_eta, &b_electron_eta);
   fChain->SetBranchAddress("electron_phi", &electron_phi, &b_electron_phi);
   fChain->SetBranchAddress("electron_ch", &electron_ch, &b_electron_ch);
   fChain->SetBranchAddress("electron_iso", &electron_iso, &b_electron_iso);
   fChain->SetBranchAddress("electron_isLoose", &electron_isLoose, &b_electron_isLoose);
   fChain->SetBranchAddress("electron_isMedium", &electron_isMedium, &b_electron_isMedium);
   fChain->SetBranchAddress("electron_isTight", &electron_isTight, &b_electron_isTight);
   fChain->SetBranchAddress("electron_dxy", &electron_dxy, &b_electron_dxy);
   fChain->SetBranchAddress("electron_dz", &electron_dz, &b_electron_dz);
   fChain->SetBranchAddress("electron_dxyError", &electron_dxyError, &b_electron_dxyError);
   fChain->SetBranchAddress("electron_dzError", &electron_dzError, &b_electron_dzError);
   Notify();
}

Bool_t Events_myelectrons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events_myelectrons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events_myelectrons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_myelectrons_cxx
