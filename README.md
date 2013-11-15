utils
=====

   myProof
   +++++++

   Example of standalone program using PROOF.
   To build, make sure ROOTSYS is valid and just type 'make'.
   This should create the executable 'myProof' which can run the ProofSimple tutorial in batch ot graphic mode:

               ./myProof lite:// -t simple -n 10000                   // batch mode, 10000 entries
               ./myProof lite:// -t simple -n 10000 -g                // graphic mode, 10000 entries

   Note that the same code can be run inside root

               root [] .L myProof.cxx+
               root [] myProof("lite://", "simple", 0, 10000)

