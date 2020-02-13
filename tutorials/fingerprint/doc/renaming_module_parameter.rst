.. :orphan:

Renaming a Module Parameter
===========================

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

1. change or action
2. phenomenon / effect
3. solution
4. example

The renaming of NED parameters can also cause regression; the parameter might be used by derived modules;
a parameter setting in a derived module might not have the effect it had before; forgetting to update ini keys can also cause problems.

.. The renaming of NED parameters can also cause regression:

   - The parameter might be used by submodules
   - A parameter setting in a derivative module might not have the effect it had before
   - Forgetting to update ini keys can also cause problems

.. TODO renaming parameters

.. TODO false positive

.. TODO example for false positive

.. To filter out false positives for regression, the fingerprints need to be calculated without the full path:

  - Before making the change, rerun fingerprints without the full path ingredient
  - Update fingerprints, as the new values can be accepted since no change taken place
  - Perform renaming
  - Run fingerprints again

  -----------------------

  - Before making the change, rerun fingerprints without the full path ingredient
  - Update fingerprints, as the new values can be accepted since no change in the model has taken place
  - Perform renaming
  - Run fingerprints again

.. --------------------------

  - Before making the change, rerun fingerprints without the full path ingredient (to do that, just delete the ``p`` from the ingredients. The fingerprint tool will calculate the fingerprints using ``tlx``)
  - Update fingerprints (Overwrite fingerprintshowcase.csv with fingerprintshowcase.csv.UPDATED), as the new values can be accepted since no change taken place
  - Perform renaming
  - Run fingerprints again

.. **TODO** run fingerprints with tlx: just delete the p from the csv file and rerun the fingerprints
   now the tlx fingerprints will be calculated...of course they are wrong because the values are from the previous tplx run...so overwrite

.. .. note:: To run fingerprints with ``tlx``, delete the ``p`` from the ingredient in the .csv file. When the fingerprint test is run again, the fingerprints will be calculated with the new ingredients. The tests will fail, as the values are still the ones calculated with ``tplx``, but it is safe to overwrite them with the updated values, as the model didn't change.

.. **TODO** should this be somewhere else ?

.. Now, if fingerprints don't pass, it indicates that the change really broke something in the model/introduced a regression.

If the fingerprint tests don't pass, it indicates that the change really broke something in the model and introduced a regression. -> not sure its needed

.. **TODO** example for a false-positive

.. The following is an example for a parameter name change causing a real regression (as opposed to a false positive). The :ned:`Router` module sets the :par:`forwarding` parameter to ``true`` which it inherits from the :ned:`NetworkLayerNodeBase` module it extends. The latter uses the parameter to enable forwarding in its various submodules, such as :ned:`Ipv4` and :ned:`Ipv6`:

The following is a simplistic example for module parameter renaming causing a regression. The :ned:`Router` module sets the :par:`forwarding` parameter to ``true`` which it inherits from the :ned:`NetworkLayerNodeBase` module it extends. The latter uses the parameter to enable forwarding in its various submodules, such as :ned:`Ipv4` and :ned:`Ipv6`:

**TODO** is there a workflow here ? or just an example...there is no workflow...the fingerprints change

-> actually, the fingerprints dont change if its done ok -> following the changes everywhere
-> the workflow is ... make the change, run the fingerprint tests, they fail, there is something wrong
-> do it right, run the fingerprint tests, they pass

.. code-block:: ned
   :emphasize-lines: 6

   module Router extends ApplicationLayerNodeBase
   {
    parameters:
        forwarding = true;

.. code-block:: ned
   :emphasize-lines: 9

   module NetworkLayerNodeBase extends LinkLayerNodeBase
   {
    parameters:
        bool forwarding = default(false);
        bool multicastForwarding = default(false);
        *.forwarding = forwarding;
        *.multicastForwarding = multicastForwarding;

.. We rename the ``forwarding`` parameter in :ned:`NetworkLayerNodeBase` to ``unicastForwarding``.
   Now, the ``forwarding = true`` key in Router doesn't take effect in the router's submodules,
   and the router doesn't forward packets. (simulations break)(fingerprints break)

.. **TODO** is the .... needed?

In :ned:`NetworkLayerNodeBase`, we rename the ``forwarding`` parameter  to ``unicastForwarding`` to make it similar to ``multicastForwarding``.
Now, the ``forwarding = true`` key in :ned:`Router` doesn't take effect in the router's submodules,
and the router doesn't forward packets.

.. (simulations break)(fingerprints break)

.. Results

.. literalinclude:: ../NetworkLayerNodeBase.ned.forwarding
   :diff: ../NetworkLayerNodeBase.ned.orig

.. code-block:: ned
   :emphasize-lines: 6

   module Router extends ApplicationLayerNodeBase
   {
    parameters:
        forwarding = true;
        ....

.. TODO this breaks tlx fingerprints

.. This change causes also the ``tlx`` fingerprints to fail, thus indicating a regression.
   When we rename the ``forwarding`` parameter in Router to ``unicastForwarding``, the fingerprints pass.

.. This model change breaks ``tplx`` and even ``tlx`` fingerprints, thus indicating a regression.
   When we rename the ``forwarding`` parameter in Router to ``unicastForwarding``, the fingerprints pass.

This change causes the fingerprint tests/``tplx`` fingerprint tests to fail:

TODO fail -> this is the same in all cases

TODO to correct the model the renaming needs to be followed everywhere/When we rename the ``forwarding`` parameter in Router to ``unicastForwarding``, the fingerprints pass.

.. TODO pass

.. TODO fail ?

.. TODO or none of them is needed

TODO pittfalls

- it can lead to error
