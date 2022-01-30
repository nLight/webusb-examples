(function() {
  'use strict';

  document.addEventListener('DOMContentLoaded', event => {
    let connectButton = document.querySelector("#connect");
    let statusDisplay = document.querySelector('#status');
    let port;
    let currentKey = 0;

    function connect() {
      port.connect().then(() => {
        statusDisplay.textContent = '';
        connectButton.textContent = 'Disconnect';

        port.onReceive = data => {
          let textDecoder = new TextDecoder();
          console.log(textDecoder.decode(data));
        }
        port.onReceiveError = error => {
          console.error(error);
        };
      }, error => {
        statusDisplay.textContent = error;
      });
    }

    let keysToFreq = {
      a: 65, // #define NOTE_C2  65
      w: 69, // #define NOTE_CS2 69
      s: 73, // #define NOTE_D2  73
      e: 78, // #define NOTE_DS2 78
      d: 82, // #define NOTE_E2  82
      f: 87, // #define NOTE_F2  87
      t: 93, // #define NOTE_FS2 93
      g: 98, // #define NOTE_G2  98
      y: 104,// #define NOTE_GS2 104
      h: 110,// #define NOTE_A2  110dd
      u: 117, // #define NOTE_AS2 117
      j: 123 // #define NOTE_B2  123
    };

    let keysToNotes = {
      a: "C2",
      w: "CS2",
      s: "D2",
      e: "DS2",
      d: "E2",
      f: "F2",
      t: "FS2",
      g: "G2",
      y: "GS2",
      h: "A2",
      u:  "AS2",
      j: "B2",
    };

    let repeatRateTimer = null;
    window.addEventListener("keydown", async function (event) {
      console.log(keysToNotes[event.key]);
      currentKey = keysToFreq[event.key];
      let view = new Uint8Array(1);
      view[0] = currentKey;
      await port.send(view);
    });
    window.addEventListener("keyup", function () {
      currentKey = 0
    });

    connectButton.addEventListener('click', function() {
      if (port) {
        port.disconnect();
        connectButton.textContent = 'Connect';
        statusDisplay.textContent = '';
        port = null;
      } else {
        serial.requestPort().then(selectedPort => {
          port = selectedPort;
          connect();
        }).catch(error => {
          statusDisplay.textContent = error;
        });
      }
    });

    serial.getPorts().then(ports => {
      if (ports.length == 0) {
        statusDisplay.textContent = 'No device found.';
      } else {
        statusDisplay.textContent = 'Connecting...';
        port = ports[0];
        connect();
      }
    });
  });
})();
