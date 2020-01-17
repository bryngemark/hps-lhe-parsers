# simp-lhe-parser

This simple program parses .lhe files into .root files specifically for the SIMP events.

First to compile the parser do,

`source build.sh`

Then run the parser with

`./lhetree_SIMP.exe <input LHE file> <output root filename> <xsec> <# events>`

Alternatively, one can also just do `source lhesnip.sh </path/to/lhe/file/.lhe>` assuming that the .lhe is contained in a the following structure: `../dir1/modeldir/Events/run_01/unweighted_events.lhe`
