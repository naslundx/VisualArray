// Not at all working yet.
// The following code describes what features to implement

// FOR THE FUTURE:
// ECMA script 6 supports Object.observe
// Adapted from https://developers.google.com/web/updates/2012/11/Respond-to-change-with-Object-observe:
/*
var beingWatched = {};

function whatHappened(change) {
    console.log(change.name + " was " + change.type + " and is now " + change.object[change.name]);
}

function somethingChanged(changes) {
    changes.forEach(whatHappened);
}

Object.observe(beingWatched, somethingChanged);
*/

// CURRENTLY:

//Some way to input the array to be monitored
//... = function(...) {
//
//};

//Color a specific element 
gfxColor = function(index, color) {

};

// Remove color of element
gfxDecolor = function(index) {

};

// Add separating line between leftindex and leftindex+1
gfxSeparate = function(leftindex, size, color) {

};

// Remove latest separator at leftindex
gfxDeseparate = function(leftindex) {

};

// Remove the latest change from the array changelog
hideLastOperation = function() {

};

// Remove the entire array changelog
clearHistory = function() {

};

// Find the next operation (if any) to affect and render
nextOperation = function() {

};

// Find the previous operation (if any) to affect and render. Used to step back
prevOperation = function() {

};

// Used to execute a specific operation (SET or SWAP) on the array content
executeOperation = function(operation) {

};

// Prepare rendering, setup rendering loop, and execute.
// The GUI dictates whether we move forward/backward/playing
render = function() {

};
