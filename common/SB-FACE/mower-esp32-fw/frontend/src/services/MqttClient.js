import { Client, connect } from 'mqtt'
import { MQTT_BROKER_URL } from 'src/config'
import _ from 'lodash'

// const mqtt = require('mqtt');
class MqttClientClass {
    //      mqtt = require('mqtt')
    // var client = mqtt.connect('mqtt://test.mosquitto.org')

    // client.on('connect', function () {
    //     client.subscribe('presence', function (err) {
    //         if (!err) {
    //             client.publish('presence', 'Hello mqtt')
    //         }
    //     })
    // })

    // client.on('message', function (topic, message) {
    //     // message is Buffer
    //     debug(message.toString())
    //     client.end()
    // })
    _subscriptions = {};
    _handlers = {};

    /** @type: Client */
    _client
    /**
     * @return Client 
     */
    /** @type: Boolean */
    get connected () {
        return this._client.connected
    }
    /** @type: Boolean */
    get reconnecting () {
        return this._client.reconnecting;
    }
    connect () {
        const options = {
            // Clean session
            clean: true,
            connectTimeout: 4000,
            // Auth
            // clientId: 'emqx_test',
            // username: 'emqx_test',
            // password: 'emqx_test',
        }
        this._client = connect(MQTT_BROKER_URL, options);
        this._onMessage();
        this._onConnected();
        this._onError();
    };
    reconnect () {
        this._client.reconnect();
    };
    publish () {
        this._client.publish(...arguments);
    }
    subscribe () {
        this._client.subscribe(...arguments);
    }
    unsubscribe () {
        this._client.unsubscribe(...arguments);
    }
    _onMessage () {
        this._client.on('message', (topic, message) => {
            // message is Buffer
            let data
            try {
                data = JSON.parse(message.toString());
            } catch (e) {
                debug('MQTT: Error parse message');
                data = message;
                // debug('MQTT: Data set to raw message');
            }
            const h = this._handlers[topic] || _.find(this._handlers, f => {
                return f.catchAll && _.startsWith(topic, f.topic.replace('#', ''));
            });
            if (h) {
                h.handler(data, topic);
            }
            // debug('GOT MESSAGE', topic, data);
        })
    }
    _onConnected () {
        this._client.on('connect', () => {
            this._subscribeAll();
        })
    }
    _onError () {
        this._client.on('error', (err) => {
            debug('MQTT: Error ', err);
        })
    }
    setMessageHandler (topic, handler, catchAll) {
        this._handlers = this._handlers || {};
        this._handlers[topic] = {
            topic,
            handler,
            catchAll
        }
    }
    unsetMessageHandler (topic) {
        if (this._handlers[topic]) {
            delete this._handlers[topic];
        }
    }
    onSubscribe () { }
    onUnsubscribe () { }
    addSubscription (topic, callback, catchAll = false) {
        this._subscriptions = this._subscriptions || {};
        this._subscriptions[topic] = {
            topic, callback
        }
        if (this.connected) {
            this.setMessageHandler(topic, callback, catchAll);
            this.subscribe(topic)
        }
    }
    removeSubscription (topic) {
        this._subscriptions = this._subscriptions || {};
        delete this._subscriptions[topic];
        if (this.connected) {
            this.unsetMessageHandler(topic);
            this.unsubscribe(topic)
        }
    }
    _subscribeAll () {
        _.each(this._subscriptions, (sub) => {
            this.setMessageHandler(sub.topic, sub.callback);
            this.subscribe(sub.topic);
        })
    }
    _unsubscribeAll () {
        _.each(this._subscriptions, (sub) => {
            this.unsetMessageHandler(sub.topic);
            this.unsubscribe(sub.topic, sub.callback);
        })
    }

}

export const MqttClient = new MqttClientClass()