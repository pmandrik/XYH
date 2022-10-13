//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 10 16:16:41 2022 by ROOT version 6.26/06
// from TTree Events_mygenparticles/Events_mygenparticles
// found on file: /home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root
//////////////////////////////////////////////////////////

#ifndef Events_mygenparticles_h
#define Events_mygenparticles_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Events_mygenparticles {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           numGenPart;
   vector<float>   *GenPart_pt;
   vector<float>   *GenPart_eta;
   vector<float>   *GenPart_mass;
   vector<int>     *GenPart_pdgId;
   vector<float>   *GenPart_phi;
   vector<float>   *GenPart_px;
   vector<float>   *GenPart_py;
   vector<float>   *GenPart_pz;
   vector<int>     *GenPart_status;

   // List of branches
   TBranch        *b_numGenPart;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_mass;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_px;   //!
   TBranch        *b_GenPart_py;   //!
   TBranch        *b_GenPart_pz;   //!
   TBranch        *b_GenPart_status;   //!

   Events_mygenparticles(TTree *tree=0);
   virtual ~Events_mygenparticles();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Events_mygenparticles_cxx
Events_mygenparticles::Events_mygenparticles(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/pmandrik/work/projects/XYH/process_ttbar2/ttbar.root:/mygenparticle");
      dir->GetObject("Events_mygenparticles",tree);

   }
   Init(tree);
}

Events_mygenparticles::~Events_mygenparticles()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Events_mygenparticles::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Events_mygenparticles::LoadTree(Long64_t entry)
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

void Events_mygenparticles::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   GenPart_pt = 0;
   GenPart_eta = 0;
   GenPart_mass = 0;
   GenPart_pdgId = 0;
   GenPart_phi = 0;
   GenPart_px = 0;
   GenPart_py = 0;
   GenPart_pz = 0;
   GenPart_status = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numGenPart", &numGenPart, &b_numGenPart);
   fChain->SetBranchAddress("GenPart_pt", &GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta", &GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_mass", &GenPart_mass, &b_GenPart_mass);
   fChain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_phi", &GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_px", &GenPart_px, &b_GenPart_px);
   fChain->SetBranchAddress("GenPart_py", &GenPart_py, &b_GenPart_py);
   fChain->SetBranchAddress("GenPart_pz", &GenPart_pz, &b_GenPart_pz);
   fChain->SetBranchAddress("GenPart_status", &GenPart_status, &b_GenPart_status);
   Notify();
}

Bool_t Events_mygenparticles::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events_mygenparticles::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Events_mygenparticles::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Events_mygenparticles_cxx
