var port = chrome.runtime.connectNative('com.stwunsch.nordvpn_status');
var data = null;

port.onMessage.addListener(function(msg) {
  data = msg;
});
