.. :orphan:

Refactoring
===========

  1. change or action
  2. phenomenon / effect
  3. solution
  4. example

There are some changes which don't change fingerprints at all, and unlikely to cause regression.
These changes include renaming C++ functions and variables, and method extraction.

For example, we extract some part of ``handleUpperCommand()`` function in the Udp module to a new function:

.. literalinclude:: ../Udp_extract.cc
   :diff: ../Udp_orig.cc

.. **Why doesn't it change the fingerprint?**

The refactoring doesn't change the fingerprint because the code is functionally the same; it doesn't create any new events or data packets, and it doesn't change timing, or anything that the fingerprint takes into account.

.. TODO: PASS

.. .. role:: green

.. :green:`PASS`

.. code-block:: fp

   $ inet_fingerprinttest
   . -f omnetpp.ini -c Wired -r 0  ... : PASS
   . -f omnetpp.ini -c Mixed -r 0  ... : PASS
   . -f omnetpp.ini -c Wireless -r 0  ... : PASS
   . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
   . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
   . -f omnetpp.ini -c Ospf -r 0  ... : PASS
   . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
   . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED
   . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : FAIL

   ----------------------------------------------------------------------
   Ran 9 tests in 24.042s

   OK

   Log has been saved to test.out
   Test results equals to expected results
