.. :orphan:

Accepting Fingerprint Changes
=============================

  TODO link here from everywhere else

  so

  if the model is verified using the previous steps,
  then the ingredients can be returned to tplx

  because the model was verified after a change
  and there was no change since then

  - replace ingredients with tplx
  - run the tests
  - overwrite the csv file
  - you may need to re-run the fingerpints to check whether they are stable (because what if each run gives you a different one? e.g. simulation trajectory depends on memory layout: e.g. iteration on std::map of object pointers)

  also, when the fingerprint tool cant be used to verify the model, it needs to be
  inspected and then it can be decided that its correct
  -> not here? thats another step ?
  NOT HERE!

**V1** If the model is verified by selecting different, temporary fingerprint ingredients, the ingredients can be changed back to the initial ones, which may be more suitable for detecting regressions.

**V2** If the model is verified after a change by selecting different, temporary fingerprint ingredients, the ingredients can be changed back to the initial ones, which may be more suitable for detecting regressions.

.. , then the temporary ones.

To do that, replace the ingredients with ``tplx`` (or other chosen set of baseline ingredients):

TODO

Then run the fingerprint tests:

TODO

The tests fail, because the fingerprint values in the .csv file correspond to the previous set of ingredients. Since there was no change in the model, it is safe to accept the new values/the new values can be accepted/it is safe to overwrite the .csv file with the new values:

TODO

**V1** It is advisable to re-run the tests to check whether the fingerprints are stable; i.e. it might happen that each run gives different values, e.g. when the simulation trajectory depends on memory layout (caused by iteration on std::map of object pointers, for example).

**V2** The fingerprint tests should be re-run to check whether they are stable (because if each run may result in different values, e.g. the simulation trajectory depends on memory layout (caused by iteration on std::map of object pointers, for example).

TODO

**TODO** if not stable, then choose other ingredients ?
