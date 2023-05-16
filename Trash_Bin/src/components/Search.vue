<script lang="ts">
import { defineComponent, render } from 'vue';
import Query_Creator from './Query_Components/Query_Creator.vue';
import Result from './Result_Components/Result.vue';
import {Types} from '../types'

type obj = { Name: string; Files: { Name: string; Extention: string; Content: string; DocID: string;}[]; Folders: { Name: string; Files: { Name: string; Extention: string; Content: string; DocID: string;}[]; Folders: never[]; }[]; }

let tempData = {
    "Name": "Root",
    "Files": [
        {
            "Name": "File1",
            "Extention": "csv",
            "Content": "1,2,3,4",
            "DocID": "1"
        },
        {
            "Name": "File2",
            "Extention": "csv",
            "Content": "5,6,7,8",
            "DocID": "2"
        }
    ],
    "Folders": [
        {
            "Name": "Folder1",
            "Files": [
                {
                    "Name": "File3",
                    "Extention": "csv",
                    "Content": "9,10,11,12\n13,14,15,16",
                    "DocID": "3"
                }
            ],
            "Folders": []
        }
    ]
}


function renderFolder(data: obj, depth: number = 0) {
    let name: string = data["Name"]
    let items: Types.Item[] = []
    let folders: Types.Folder[] = []
    for(let file = 0; file < data["Files"].length; file++) {
        items.push(new Types.Item(data["Files"][file]["Name"], data["Files"][file]["Extention"], data["Files"][file]["Content"], data["Files"][file]["DocID"], depth + 1))
    }
    for(let folder = 0; folder < data["Folders"].length; folder++) {
        console.log(data["Folders"][folder])
        folders.push(renderFolder(data["Folders"][folder], depth + 1))
    }
    return new Types.Folder(name, folders, items, false, depth)
}

export default defineComponent ({
        components: {
            Query_Creator,
            Result
        },
        methods: {
            renderFileTree(data: obj[]) {
                console.log("Building Tree")

                data = [tempData, tempData]
                this.data = []
                for (let folder = 0; folder < data.length; folder++) {
                    this.data.push(renderFolder(data[folder]))
                }

                this.loaded = true
                this.$forceUpdate();
            }
        },
        data() {return {
            loaded: false,
            data: [new Types.Folder("",[],[])]
        }}
    })
</script>

<template>
    <h2 @click="renderFileTree([])">Search Menu</h2>
    <Query_Creator @loaded="renderFileTree" />
    <div v-if="loaded" v-for="folder in data">
        <Result :data="folder"/>
    </div>
</template>