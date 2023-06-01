import type { Types } from './types'

const baseURL = "http://localhost:18080/api/rest/v1/json/"

export async function sendQuery(keys: string[], selected: Map<string, string>) {
    let query: { key: string, value?: string }[] = []
    keys.forEach((key) => {
        if (selected.get(key) != null) {
            query.push({ key: key, value: selected.get(key) })
        } else {
            //query.push({key: key, value: ""})
        }
    })
    let url = baseURL + "query/"
    query.forEach((item) => {
        url += item.key + "=" + item.value + "&"
    })
    url = url.slice(0, url.length - 1)
    console.log(url)
    const response = await fetch(url)
    const data = await response.json()
    console.log(data)
    return data
}

export async function sendCreate(item: Types.Item, parentFolder: Types.Folder) {
    let url = baseURL + "create/file/" + encodeURI(item.name) + "/" + encodeURI(parentFolder["nodeID"]).split("/").join("%2F") + "/" + encodeURI(item.content)
    console.log(url)
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendDelete(item: Types.Item) {
    let url = baseURL + "delete/file/" + item.docID
    console.log(url)
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendDeleteFolder(folder: Types.Folder) {
    let url = baseURL + "delete/folder/" + folder.nodeID.split("/").join("%2F")
    console.log(url)
    const response = await fetch(url)
    const data = await response.json()
    return data
}

export async function sendUpdate(item: Types.Item) {
    let url = baseURL + "update/" + item.docID + "/" + item.content
    console.log(url)
    const response = await fetch(url)
    const data = await response.json()
    return data
}