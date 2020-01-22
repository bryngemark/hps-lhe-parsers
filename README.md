# hps-lhe-parsers

This set of simple programs parses .lhe files into .root files for given processes.

First to compile the parsers do,

`source build.sh`

Then run a parser with

`./lhetree_SIMP.exe <input LHE file> <output root filename> <xsec> <# events>`

Alternatively, one can also just do `source lhesnip.sh </path/to/lhe/file/.lhe>` assuming that the .lhe is contained in the following directory structure with respect to the script: `../dir1/modeldir/Events/run_01/unweighted_events.lhe`
