const findPrime = require("./findPrime");
const findPrimeNative = require("./build/Release/findprimes");

const input = 20000;

let result;

console.time("Native");
result = findPrimeNative(input, 10);
console.timeEnd("Native");
console.log(result);

console.time("JS Find Primes");
result = findPrime(input);
console.timeEnd("JS Find Primes");
console.log(result);

/*
const { WebcastPushConnection } = require("tiktok-live-connector");

// Username of someone who is currently live
let tiktokUsername = "_isurprised_";

// Create a new wrapper object and pass the username
let tiktokLiveConnection = new WebcastPushConnection(tiktokUsername);

// Connect to the chat (await can be used as well)
tiktokLiveConnection
  .connect()
  .then((state) => {
    console.info(`Connected to roomId ${state.roomId}`);
  })
  .catch((err) => {
    console.error("Failed to connect", err);
  });

// Define the events that you want to handle
// In this case we listen to chat messages (comments)
tiktokLiveConnection.on("chat", (data) => {
  console.log(
    `${data.uniqueId} (userId:${data.userId}) writes: ${data.comment}`
  );

  if (data.comment[0] == "/") {
    keySender.sendKeys(["a", "b"]);
  }
});

// And here we receive gifts sent to the streamer
tiktokLiveConnection.on("gift", (data) => {
  console.log(
    `${data.uniqueId} (userId:${data.userId}) sends ${data.giftName}`
  );
});
*/
