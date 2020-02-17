.. :orphan:

Renaming a Submodule
====================

.. TODO focus on the correct workflow and mention typical pitfalls, etc.

.. TODO lehet olyan is, hogy a rename utan a tlx ERROR vagy FAILED (modules cross-referencing each other)

.. - rename modules in the model
   - the fingerprint breaks because by default its tplx (or is it ?)
   - so drop the p (full path) from the ingredients
   - rerun fingerprints without p
   - make the change
   - the fingerprints match



.. sturcture

   - X change breaks fingerprint
   - because something
   - solution
   - example

.. 1. change or action
   2. phenomenon / effect
   3. solution
   4. example

Renaming submodules can cause the fingerprints to change, because the default ingredients (``tplx``) contain the full module path, thus the submodule name as well. Renaming submodules can cause regression in some cases, e.g. when functionality depends on submodule names (e.g. submodules referring to each other).

.. The renaming of NED parameters can also cause regression; the parameter might be used by derived modules;
   a parameter setting in a derived module might not have the effect it had before; forgetting to update ini keys can also cause problems.

.. The renaming of NED parameters can also cause regression:

   - The parameter might be used by submodules
   - A parameter setting in a derivative module might not have the effect it had before
   - Forgetting to update ini keys can also cause problems

.. TODO renaming parameters

.. TODO false positive

.. TODO example for false positive

.. To filter out false positives for regression, the fingerprints need to be calculated without the full path:

.. To go around the problem of fingerprints failing due to the name change, the fingerprints need to be calculated without the full path:

To go around the problem of fingerprints failing due to renaming, the fingerprints need to be calculated without the full path:

.. - Before making the change, rerun fingerprints without the full path ingredient
   - Update fingerprints, as the new values can be accepted since no change taken place
   - Perform renaming
   - Run fingerprints again

   -----------------------

   - Before making the change, rerun fingerprints without the full path ingredient
   - Update fingerprints, as the new values can be accepted since no change in the model has taken place
   - Perform renaming
   - Run fingerprints again

   ------------------------

- Before making the change, rerun fingerprint tests without the full path ingredient
- Update fingerprints; the new values can be accepted because the model didn't change
- Perform renaming
- Run fingerprint tests again

.. --------------------------

  - Before making the change, rerun fingerprints without the full path ingredient (to do that, just delete the ``p`` from the ingredients. The fingerprint tool will calculate the fingerprints using ``tlx``)
  - Update fingerprints (Overwrite fingerprintshowcase.csv with fingerprintshowcase.csv.UPDATED), as the new values can be accepted since no change taken place
  - Perform renaming
  - Run fingerprints again

.. **TODO** run fingerprints with tlx: just delete the p from the csv file and rerun the fingerprints
   now the tlx fingerprints will be calculated...of course they are wrong because the values are from the previous tplx run...so overwrite

.. note:: To run fingerprints with ``tlx``, delete the ``p`` from the ingredient in the .csv file. When the fingerprint test is run again, the fingerprints will be calculated with the new ingredients. The tests will fail, as the values are still the ones calculated with ``tplx``, but it is safe to overwrite them with the updated values, as the model didn't change.

.. **TODO** should this be somewhere else ?

.. Now, if fingerprints don't pass, it indicates that the change really broke something in the model/introduced a regression.

.. x

  If the fingerprint tests don't pass, it indicates that the change really broke something in the model and introduced a regression. -> doesn't seem to be needed here

.. **TODO** example for a false-positive

.. **V0** The workflow is the following:

.. **V1** Here is an example for the workflow above:

.. **V2** Here is a simplistic example demonstrating the workflow:

Here is the workflow demonstrated using a simplistic example:

.. We run the fingerprint tests with ``tlx`` ingredients:

We set the fingerprint ingredients to ``tlx``:

.. (drop the ``p``/or the note above)

.. TODO ingredients replaced with tlx + FAIL

.. code-block:: text

  .,        -f omnetpp.ini -c Wireless -r 0,        5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Mixed -r 0,           5s,         2057-99b2/tlx, PASS,
  .,        -f omnetpp.ini -c Wired -r 0,           5s,         b39c-715b/tlx, PASS,
  .,        -f omnetpp.ini -c WirelessNID -r 0,     5s,         d410-0d99/NID,  PASS,
  .,        -f omnetpp.ini -c WiredNID -r 0,        5s,         1145-0392/NID,  PASS,
  .,        -f omnetpp.ini -c MixedNID -r 0,        5s,         d2fb-2f48/NID,  PASS,
  .,        -f omnetpp.ini -c WirelessNIDDim -r 0,  5s,         d410-0d99/NID,  PASS,
  .,        -f omnetpp.ini -c WirelessDim -r 0,     5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Ospf -r 0,            5000s,      0cf5-6ae4/tlx, PASS,

Then we run the fingerprint tests:

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Ospf -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

As expected, they fail because the values are still the ones calculated with ``tplx``.
We can update the .csv file with the new values:

.. /the note above

.. Then, they can be updated:

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

**TODO** show that if we run the tests again they pass -> just for now, not needed later

As a simplisic example, we rename the ``eth`` module vector to ``ethernet`` in :ned:`LinkLayerNodeBase` and :ned:`NetworkLayerNodeBase`. This change affects all host-types such as :ned:`StandardHost` and :ned:`AdhocHost` since they are derived modules:

.. TODO example for no regression (rename some module)

.. literalinclude:: ../LinkLayerNodeBase.ned.modified
   :diff: ../LinkLayerNodeBase.ned.orig

.. literalinclude:: ../NetworkLayerNodeBase.ned.modified
   :diff: ../NetworkLayerNodeBase.ned.orig

.. As expected, when running the fingerprints/fingerprint tests, they fail:

We run the fingerprint tests again:

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

As expected, the fingerprints didn't change, so we can assume the model is correct.

TODO: change to tplx, rerun, and accept (show all steps)

However, renaming submodules can lead to ERROR in the fingerprint tests, e.g. when modules cross-reference each other and look for other modules by name. Also, renaming can lead to FAILED fingerprint tests, because there might be no check in the model on cross-referencing module names.

TODO: show an example for FAIL and ERROR

.. Because there was no change in the model./only the names changed

..  / the fingerprint tests pass

.. **TODO** fingerprint FAILED

.. .. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Ospf -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

.. We revert the change, then run the fingerprints/fingerprint tests with ingredients ``tlx``, and update ``fingerprintshowcase.csv`` with the new values:

.. **TODO** csv

.. .. code-block:: text

  .,        -f omnetpp.ini -c Wireless -r 0,        5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Mixed -r 0,           5s,         2057-99b2/tlx, PASS,
  .,        -f omnetpp.ini -c Wired -r 0,           5s,         b39c-715b/tlx, PASS,
  .,        -f omnetpp.ini -c WirelessNID -r 0,     5s,         d410-0d99/NID, PASS,
  .,        -f omnetpp.ini -c WiredNID -r 0,        5s,         1145-0392/NID, PASS,
  .,        -f omnetpp.ini -c MixedNID -r 0,        5s,         d2fb-2f48/NID, PASS,
  .,        -f omnetpp.ini -c WirelessNIDDim -r 0,  5s,         d410-0d99/NID, PASS,
  .,        -f omnetpp.ini -c WirelessDim -r 0,     5s,         d477-98c9/tlx, PASS,
  .,        -f omnetpp.ini -c Ospf -r 0,            5000s,      0cf5-6ae4/tlx, PASS,

.. After making the change and running the fingerprints, they pass:

.. **TODO** fingerprint PASS

.. .. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

.. ----

.. TODO example for regression (rename some module that is referred to by name, such as ip or routing table) -> leads to an error rather than failed fingerprints

.. maybe renaming a host or something? that is not a src/inet ned change

.. TODO renaming breaks the tplx fingerprints

.. TODO pitfalls

  - renaming submodules can lead to error when modules cross reference each other/look for other modules by name
  - it can lead to fail because there might be no check on some submodule name and if it is found
  - but these are indicated...the tlx fingerprints dont pass
