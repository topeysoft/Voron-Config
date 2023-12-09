
export function objectize (message) {
    let data = message || '';
    try {
        data = JSON.parse(data)
        data.payload = objectize(data.payload);
    } catch (error) {

    }
    return data;
}