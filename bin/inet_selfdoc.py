#!/usr/bin/env python3

import json

with open('SelfDoc_step01.json', 'r') as f:
    content = "[" + f.read() + '{} ]'  # make an array from the individual dictionary items in the file and add an empty entry at the end to avoid issues with th trailing comma
    database = json.loads(content)

nedtypes = dict()

for entry in database:
    if entry : # skip empty entries (so you can add an empty entry at the end of the file)
        nedtypes[entry["module"]] = actions = nedtypes.get(entry["module"], dict())
        actions[entry["action"]] = details = actions.get(entry["action"], list())
        details.append(entry["details"])

with open('SelfDoc.json', 'w') as f:
    f.write(json.dumps(nedtypes, indent=True))
    f.close
