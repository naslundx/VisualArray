// Not implemented yet.
// ECMA script 6 supports Object.observe

// Adapted from https://developers.google.com/web/updates/2012/11/Respond-to-change-with-Object-observe:

var beingWatched = {};

function whatHappened(change) {
    console.log(change.name + " was " + change.type + " and is now " + change.object[change.name]);
}

function somethingChanged(changes) {
    changes.forEach(whatHappened);
}

Object.observe(beingWatched, somethingChanged);