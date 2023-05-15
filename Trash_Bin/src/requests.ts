import type {Types} from './types'

const baseURL = "http://localhost:18080/api/rest/v1/json/"

export async function sendQuery(keys: string[], selected: Map<string, string>) {
    let query:{key: string, value?: string}[] = []
    keys.forEach((key) => {
        if (selected.get(key) != null) {
            query.push({key: key, value: selected.get(key)})
        } else {
            //query.push({key: key, value: ""})
        }
    })
    let url = baseURL + "query/"
    query.forEach((item) => {
        url += item.key + "=" + item.value + "&"
    })
    url = url.slice(0, url.length - 1)
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendCreate(item: Types.Item) {
    let url = baseURL + "create/" + item.content
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendDelete(item: Types.Item) {
    let url = baseURL + "delete/" + item.docID
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendUpdate(item: Types.Item) {
    let url = baseURL + "update/" + item.docID + "/" + item.content
    const response = await fetch(url)
    const data = await response.json()
    return data
}