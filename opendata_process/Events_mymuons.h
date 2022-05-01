//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  1 00:25:23 2022 by ROOT version 6.26/02
// from TTree Events_mymuons/Events
// found on file: /home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root
//////////////////////////////////////////////////////////

#ifndef Events_mymuons_h
#define Events_mymuons_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Events_mymuons {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           numbermuon;
   vector<float>   *muon_e;
   vector<float>   *muon_pt;
   vector<float>   *muon_px;
   vector<float>   *muon_py;
   vector<float>   *muon_pz;
   vector<float>   *muon_eta;
   vector<float>   *muon_phi;
   vector<float>   *muon_ch;
   vector<int>     *muon_isSoft;
   vector<int>     *muon_isTight;
   vector<float>   *muon_dxy;
   vector<float>   *muon_dz;
   vector<float>   *muon_dxyError;
   vector<float>   *muon_dzError;
   vector<float>   *muon_pfreliso03all;
   vector<float>   *muon_pfreliso04all;
   vector<float>   *muon_jetidx;
   vector<float>   *muon_genpartidx;

   // List of branches
   TBranch        *b_numbermuon;   //!
   TBranch        *b_muon_e;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_px;   //!
   TBranch        *b_muon_py;   //!
   TBranch        *b_muon_pz;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_ch;   //!
   TBranch        *b_muon_isSoft;   //!
   TBranch        *b_muon_isTight;   //!
   TBranch        *b_muon_dxy;   //!
   TBranch        *b_muon_dz;   //!
   TBranch        *b_muon_dxyError;   //!
   TBranch        *b_muon_dzError;   //!
   TBranch        *b_muon_pfreliso03all;   //!
   TBranch        *b_muon_pfreliso04all;   //!
   TBranch        *b_muon_jetidx;   //!
   TBranch        *b_muon_genpartidx;   //!

   Events_mymuons(TTree *tree=0);
   virtual ~Events_mymuons();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_mymuons_cxx
Events_mymuons::Events_mymuons(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root:/mymuons");
      dir->GetObject("Events_mymuons",tree);

   }
   Init(tree);
}

Events_mymuons::~Events_mymuons()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events_mymuons::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events_mymuons::LoadTree(Long64_t entry)
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

void Events_mymuons::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   muon_e = 0;
   muon_pt = 0;
   muon_px = 0;
   muon_py = 0;
   muon_pz = 0;
   muon_eta = 0;
   muon_phi = 0;
   muon_ch = 0;
   muon_isSoft = 0;
   muon_isTight = 0;
   muon_dxy = 0;
   muon_dz = 0;
   muon_dxyError = 0;
   muon_dzError = 0;
   muon_pfreliso03all = 0;
   muon_pfreliso04all = 0;
   muon_jetidx = 0;
   muon_genpartidx = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numbermuon", &numbermuon, &b_numbermuon);
   fChain->SetBranchAddress("muon_e", &muon_e, &b_muon_e);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_px", &muon_px, &b_muon_px);
   fChain->SetBranchAddress("muon_py", &muon_py, &b_muon_py);
   fChain->SetBranchAddress("muon_pz", &muon_pz, &b_muon_pz);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_ch", &muon_ch, &b_muon_ch);
   fChain->SetBranchAddress("muon_isSoft", &muon_isSoft, &b_muon_isSoft);
   fChain->SetBranchAddress("muon_isTight", &muon_isTight, &b_muon_isTight);
   fChain->SetBranchAddress("muon_dxy", &muon_dxy, &b_muon_dxy);
   fChain->SetBranchAddress("muon_dz", &muon_dz, &b_muon_dz);
   fChain->SetBranchAddress("muon_dxyError", &muon_dxyError, &b_muon_dxyError);
   fChain->SetBranchAddress("muon_dzError", &muon_dzError, &b_muon_dzError);
   fChain->SetBranchAddress("muon_pfreliso03all", &muon_pfreliso03all, &b_muon_pfreliso03all);
   fChain->SetBranchAddress("muon_pfreliso04all", &muon_pfreliso04all, &b_muon_pfreliso04all);
   fChain->SetBranchAddress("muon_jetidx", &muon_jetidx, &b_muon_jetidx);
   fChain->SetBranchAddress("muon_genpartidx", &muon_genpartidx, &b_muon_genpartidx);
   Notify();
}

Bool_t Events_mymuons::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events_mymuons::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events_mymuons::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_mymuons_cxx
