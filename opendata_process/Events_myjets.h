//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  1 00:25:24 2022 by ROOT version 6.26/02
// from TTree Events_myjets/Events
// found on file: /home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root
//////////////////////////////////////////////////////////

#ifndef Events_myjets_h
#define Events_myjets_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Events_myjets {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           numberjet;
   vector<float>   *jet_e;
   vector<float>   *jet_pt;
   vector<float>   *jet_px;
   vector<float>   *jet_py;
   vector<float>   *jet_pz;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_ch;
   vector<float>   *jet_mass;
   vector<double>  *jet_btag;
   vector<float>   *jet_pt_uncorr;

   // List of branches
   TBranch        *b_numberjet;   //!
   TBranch        *b_jet_e;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_px;   //!
   TBranch        *b_jet_py;   //!
   TBranch        *b_jet_pz;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_ch;   //!
   TBranch        *b_jet_mass;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_pt_uncorr;   //!

   Events_myjets(TTree *tree=0);
   virtual ~Events_myjets();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_myjets_cxx
Events_myjets::Events_myjets(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/pmandrik/work/projects/XYH/process_ttbar/ttbar.root:/myjets");
      dir->GetObject("Events_myjets",tree);

   }
   Init(tree);
}

Events_myjets::~Events_myjets()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events_myjets::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events_myjets::LoadTree(Long64_t entry)
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

void Events_myjets::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_e = 0;
   jet_pt = 0;
   jet_px = 0;
   jet_py = 0;
   jet_pz = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_ch = 0;
   jet_mass = 0;
   jet_btag = 0;
   jet_pt_uncorr = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numberjet", &numberjet, &b_numberjet);
   fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_px", &jet_px, &b_jet_px);
   fChain->SetBranchAddress("jet_py", &jet_py, &b_jet_py);
   fChain->SetBranchAddress("jet_pz", &jet_pz, &b_jet_pz);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_ch", &jet_ch, &b_jet_ch);
   fChain->SetBranchAddress("jet_mass", &jet_mass, &b_jet_mass);
   fChain->SetBranchAddress("jet_btag", &jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jet_pt_uncorr", &jet_pt_uncorr, &b_jet_pt_uncorr);
   Notify();
}

Bool_t Events_myjets::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events_myjets::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events_myjets::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_myjets_cxx
