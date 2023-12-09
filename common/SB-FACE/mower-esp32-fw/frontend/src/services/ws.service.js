
import _ from 'lodash';
import { objectize } from 'src/utils/helpers';

class WebSocketClient {
    constructor() {
        this.onInit = () => { }
        this.onConnect = (data) => { }
        this.onBeforeAuth = () => { }
        this.onAuthSuccess = (data) => { }
        this.onAuthFailure = (data) => { }
        this.onDisconnect = (data) => { }
        this._onMessage = (data) => { }
        this.onParseError = (err, data) => { }
        this.onBeforeReconnectAttempt = () => { }
        this.onBeforeReconnect = () => { }
        this.onBeforeAuthRetry = () => { }
        this.onBeforeDestroy = () => { }
        this.onError = (data) => { }
        this.onDestroy = () => { }
        this.tokenFactory = () => {

        }
        this.keepAlive = true;
        this._messageTypeHandlers = {};
    }
    init (wsUrl, keepAlive = true) {
        this.wsUrl = wsUrl;
        this.keepAlive = keepAlive
        this._delay = 5;
        console.log(`WebSocket: Initialized!`);
        if (this.onInit) this.onInit(this)
        this.connect();
        this._keepConnectionAlive();
        return this;
    }
    requestData (type, device_uuid) {
        if (this.authenticated && this.connected) {
            console.log(`WebSocket: Requesting data...`);
            let message = {
                type: 'data_request',
                data: {
                    device_uuid,
                    request_type: type
                }
            }
            this._sendMessage(message)
        }
    }
    connect (keepAlive) {
        console.log(`WebSocket: Connecting...`);
        if (typeof keepAlive !== 'undefined') {
            this.keepAlive = keepAlive;
        }
        this._resetFlags()
        this.connecting = true
        this.websocket = new WebSocket(this.wsUrl);
        this.websocket.onopen = (args) => {
            this._openHandler(args);
        }
        this.websocket.onmessage = (args) => {
            this._messageHandler(args);
        }
        this.websocket.onclose = (args) => {
            this._closeHandler(args);
        }
        this.websocket.onerror = (args) => {
            this._errorHandler(args);
        }
        return this;
    }
    disconnect () {
        console.log(`WebSocket: Disconnecting...`);
        this._resetFlags()
        this.websocket.close();
        return this;
    }
    destroy () {
        this._resetFlags()
        console.log(`WebSocket: Cleaning up`);
        if (this.onDestroy) this.onDestroy(this)
        if (!this.websocket) return;
        this.websocket.close();
        this.websocket = null
    }

    _resetFlags () {
        this.connected = false;
        this.connecting = false
        this.authenticating = false;
        this.authenticated = false;
    }
    _keepConnectionAlive () {
        if (this.keepAlive && !this.connected
            && !this.authenticating
            && !this.connecting
            && !this.authenticated) {
            console.log(`WebSocket: Connection lost, will attempt to reconnect`);
            if (this.onBeforeReconnectAttempt) this.onBeforeReconnectAttempt(this)
            if (!this.connected) {
                if (this.onBeforeReconnect) this.onBeforeReconnect(this)
                this.connect();
            } else if (!this.authenticated) {
                if (this.onBeforeAuthRetry) this.onBeforeAuthRetry(this)
                this._authenticate();
            }
        }
        setTimeout(() => {
            this._keepConnectionAlive()
        }, this._delay * 1000)
    }
    _authenticate () {
        let auth_token = ""
        if (this.onBeforeAuth) {
            auth_token = this.onBeforeAuth(this)
        }
        console.info('WebSocket: Connected, begining authentication');
        this.authenticating = true;
        if (!auth_token && this.tokenFactory) {
            console.info('WebSocket: fetching access token');
            auth_token = this.tokenFactory()
        }
        const msg = {
            type: 'authenticate',
            data: { token: auth_token }
        };
        const auth_msg = JSON.stringify(msg);
        this.websocket.send(auth_msg);
    }
    _sendMessage (message) {
        const msg_str = JSON.stringify(message);
        this.websocket.send(msg_str);
    }
    _closeHandler (msg) {
        console.log(`WebSocket: Closed. code: ${msg.code}`);
        if (this.onDisconnect) this.onDisconnect(this, msg)
        if (!this.keepAlive) this.destroy()
    }
    _openHandler (msg) {
        this.connecting = false
        this.connected = true
        if (this.onConnect) this.onConnect(this, msg);
        this._authenticate()
    }
    _errorHandler (msg) {
        console.error('WebSocket: Error - message: ', msg);
        if (this.onError) this.onError(this, msg)
        this.destroy();
    }
    _messageHandler (message) {
        const data = objectize(message.data);
        if (data.type === 'authSuccess') {
            this.authenticating = false;
            this.authenticated = true;
            console.info('WebSocket: Connected and authenticated');
            if (this.onAuthSuccess) this.onAuthSuccess(this, data);
        } else if (data.type === 'authFailure') {
            this.authenticating = false;
            this.authenticated = false;
            console.error('WebSocket: authentication failed');
            if (this.onAuthFailure) this.onAuthFailure(this, data);
        } else if (data.type === 'error') {
            if (this.onError) this.onError(this, data);
        }

        if (data.type && typeof this._messageTypeHandlers[data.type] === "function") {
            this._messageTypeHandlers[data.type](objectize(data.data));
        }
        if (typeof this._onMessage === "function") {
            this._onMessage(data);
        }
    }

    setMessageHandler (handler) {
        if (typeof handler !== "function") throw new Error('Handler of type function is required')
        this._onMessage = handler;
    }
    setHandler (messageType, handler) {
        if (!messageType || typeof messageType !== 'string') throw new Error('Message Type of type string is required')
        if (typeof handler !== "function") throw new Error('Handler of type function is required')
        this._messageTypeHandlers[messageType] = handler;
    }
    unsetHandler (messageType) {
        if (!messageType || typeof messageType !== 'string') throw new Error('Message Type of type string is required')
        delete this._messageTypeHandlers[messageType];
    }
    unsetAllHandlers () {
        this._messageTypeHandlers = {}
    }
};

class WebSocketManager {
    constructor() {
        this._connections = {}
    }

    createConnection (id, url, keepAlive = true) {
        if (!id) {
            throw new Error('Connection ID is required')
        }
        if (this._connections[id]) {
            throw new Error('Connection exists with this, try starting it instead')
        }
        const client = new WebSocketClient();
        this._connections[id] = client;
        client.init(url, keepAlive);
        return client;
    }
    stopConnection (id) {
        if (!id) {
            throw new Error('Connection ID is required')
        }
        const client = this._connections[id]
        if (!client) return;
        client.keepAlive = false;
        return client.disconnect();
    }
    startConnection (id, keepAlive = true) {
        if (!id) {
            throw new Error('Connection ID is required')
        }
        const client = this._connections[id]
        if (!client) {
            throw new Error('Connection does not exist for this id ')
        }
        client.keepAlive = keepAlive;
        client.connect();
        return client.disconnect();
    }
    destroyConnection (id) {
        if (!id) {
            throw new Error('Connection ID is required')
        }
        const client = this._connections[id]
        if (!client) {
            return;
        }
        client.keepAlive = false;
        client.destroy();
        delete this._connections[id];
    }
}

const WebsocketConnectionManager = new WebSocketManager;

export default WebsocketConnectionManager;
