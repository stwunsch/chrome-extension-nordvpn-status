var port = chrome.runtime.connectNative('com.stwunsch.nordvpn_status');
var data = null;
var state = null;

port.onMessage.addListener(function(msg) {
  data = msg;
  var new_state = true;
  if (data && (!data.success || (data.success && data["Status"] != "Connected"))) {
      new_state = false;
  }
  if (state == null || new_state != state) {
    state = new_state;
    var tag = "";
    if (!state) tag = "-red";
    chrome.browserAction.setIcon({
      path:
        {
          19: "icon" + tag + "-19.png",
          48: "icon" + tag + "-48.png",
          128: "icon" + tag + "-128.png"
        }
    })
  }
});
