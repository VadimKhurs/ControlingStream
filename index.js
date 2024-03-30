const findPrimeNative = require("./build/Release/findprimes");
const giftsCommands = require("./build/Release/giftsCommands");
//console.time("Native");

//let command = "/i right";
let gift = "Hello";
////findprimes(command.replace("/", ""));
giftsCommands(gift);
//console.timeEnd("Native");

/*
const { WebcastPushConnection } = require("tiktok-live-connector");

// Username of someone who is currently live
let tiktokUsername = "the.monster32";

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

  findPrimeNative(data.comment);

  /*if (data.comment[0] == "/") {
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
